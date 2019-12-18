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
struct multipath {int /*<<< orphan*/  work_mutex; } ;
struct dm_target {int /*<<< orphan*/  table; struct multipath* private; } ;
struct dm_dev {int dummy; } ;
typedef  int /*<<< orphan*/  action_fn ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int action_dev (struct multipath*,struct dm_dev*,int /*<<< orphan*/ ) ; 
 int bypass_pg_num (struct multipath*,char*,int) ; 
 int dm_get_device (struct dm_target*,char*,int /*<<< orphan*/ ,struct dm_dev**) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,struct dm_dev*) ; 
 scalar_t__ dm_suspended (struct dm_target*) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_path ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int queue_if_no_path (struct multipath*,int,int) ; 
 int /*<<< orphan*/  reinstate_path ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int switch_pg_num (struct multipath*,char*) ; 

__attribute__((used)) static int multipath_message(struct dm_target *ti, unsigned argc, char **argv,
			     char *result, unsigned maxlen)
{
	int r = -EINVAL;
	struct dm_dev *dev;
	struct multipath *m = ti->private;
	action_fn action;

	mutex_lock(&m->work_mutex);

	if (dm_suspended(ti)) {
		r = -EBUSY;
		goto out;
	}

	if (argc == 1) {
		if (!strcasecmp(argv[0], "queue_if_no_path")) {
			r = queue_if_no_path(m, true, false);
			goto out;
		} else if (!strcasecmp(argv[0], "fail_if_no_path")) {
			r = queue_if_no_path(m, false, false);
			goto out;
		}
	}

	if (argc != 2) {
		DMWARN("Invalid multipath message arguments. Expected 2 arguments, got %d.", argc);
		goto out;
	}

	if (!strcasecmp(argv[0], "disable_group")) {
		r = bypass_pg_num(m, argv[1], true);
		goto out;
	} else if (!strcasecmp(argv[0], "enable_group")) {
		r = bypass_pg_num(m, argv[1], false);
		goto out;
	} else if (!strcasecmp(argv[0], "switch_group")) {
		r = switch_pg_num(m, argv[1]);
		goto out;
	} else if (!strcasecmp(argv[0], "reinstate_path"))
		action = reinstate_path;
	else if (!strcasecmp(argv[0], "fail_path"))
		action = fail_path;
	else {
		DMWARN("Unrecognised multipath message received: %s", argv[0]);
		goto out;
	}

	r = dm_get_device(ti, argv[1], dm_table_get_mode(ti->table), &dev);
	if (r) {
		DMWARN("message: error getting device %s",
		       argv[1]);
		goto out;
	}

	r = action_dev(m, dev, action);

	dm_put_device(ti, dev);

out:
	mutex_unlock(&m->work_mutex);
	return r;
}