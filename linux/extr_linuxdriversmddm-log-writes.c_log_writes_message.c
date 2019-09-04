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
struct log_writes_c {int dummy; } ;
struct dm_target {struct log_writes_c* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,...) ; 
 int EINVAL ; 
 int log_mark (struct log_writes_c*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int log_writes_message(struct dm_target *ti, unsigned argc, char **argv,
			      char *result, unsigned maxlen)
{
	int r = -EINVAL;
	struct log_writes_c *lc = ti->private;

	if (argc != 2) {
		DMWARN("Invalid log-writes message arguments, expect 2 arguments, got %d", argc);
		return r;
	}

	if (!strcasecmp(argv[0], "mark"))
		r = log_mark(lc, argv[1]);
	else
		DMWARN("Unrecognised log writes target message received: %s", argv[0]);

	return r;
}