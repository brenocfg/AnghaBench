#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct selector {int /*<<< orphan*/  lock; int /*<<< orphan*/  valid_paths; } ;
struct path_selector {struct selector* context; } ;
struct path_info {unsigned int repeat_count; unsigned int relative_throughput; int /*<<< orphan*/  list; int /*<<< orphan*/  in_flight_size; struct dm_path* path; } ;
struct dm_path {struct path_info* pscontext; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN_LIMIT (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int ST_MAX_RELATIVE_THROUGHPUT ; 
 unsigned int ST_MIN_IO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct path_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sscanf (char*,char*,unsigned int*,char*) ; 

__attribute__((used)) static int st_add_path(struct path_selector *ps, struct dm_path *path,
		       int argc, char **argv, char **error)
{
	struct selector *s = ps->context;
	struct path_info *pi;
	unsigned repeat_count = ST_MIN_IO;
	unsigned relative_throughput = 1;
	char dummy;
	unsigned long flags;

	/*
	 * Arguments: [<repeat_count> [<relative_throughput>]]
	 * 	<repeat_count>: The number of I/Os before switching path.
	 * 			If not given, default (ST_MIN_IO) is used.
	 * 	<relative_throughput>: The relative throughput value of
	 *			the path among all paths in the path-group.
	 * 			The valid range: 0-<ST_MAX_RELATIVE_THROUGHPUT>
	 *			If not given, minimum value '1' is used.
	 *			If '0' is given, the path isn't selected while
	 * 			other paths having a positive value are
	 * 			available.
	 */
	if (argc > 2) {
		*error = "service-time ps: incorrect number of arguments";
		return -EINVAL;
	}

	if (argc && (sscanf(argv[0], "%u%c", &repeat_count, &dummy) != 1)) {
		*error = "service-time ps: invalid repeat count";
		return -EINVAL;
	}

	if (repeat_count > 1) {
		DMWARN_LIMIT("repeat_count > 1 is deprecated, using 1 instead");
		repeat_count = 1;
	}

	if ((argc == 2) &&
	    (sscanf(argv[1], "%u%c", &relative_throughput, &dummy) != 1 ||
	     relative_throughput > ST_MAX_RELATIVE_THROUGHPUT)) {
		*error = "service-time ps: invalid relative_throughput value";
		return -EINVAL;
	}

	/* allocate the path */
	pi = kmalloc(sizeof(*pi), GFP_KERNEL);
	if (!pi) {
		*error = "service-time ps: Error allocating path context";
		return -ENOMEM;
	}

	pi->path = path;
	pi->repeat_count = repeat_count;
	pi->relative_throughput = relative_throughput;
	atomic_set(&pi->in_flight_size, 0);

	path->pscontext = pi;

	spin_lock_irqsave(&s->lock, flags);
	list_add_tail(&pi->list, &s->valid_paths);
	spin_unlock_irqrestore(&s->lock, flags);

	return 0;
}