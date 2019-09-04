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
struct switch_ctx {int dummy; } ;
struct dm_target {struct switch_ctx* private; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int process_set_region_mappings (struct switch_ctx*,unsigned int,char**) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int switch_message(struct dm_target *ti, unsigned argc, char **argv,
			  char *result, unsigned maxlen)
{
	static DEFINE_MUTEX(message_mutex);

	struct switch_ctx *sctx = ti->private;
	int r = -EINVAL;

	mutex_lock(&message_mutex);

	if (!strcasecmp(argv[0], "set_region_mappings"))
		r = process_set_region_mappings(sctx, argc, argv);
	else
		DMWARN("Unrecognised message received.");

	mutex_unlock(&message_mutex);

	return r;
}