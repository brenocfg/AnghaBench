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
struct dm_target {int /*<<< orphan*/  table; } ;
struct dm_dirty_log {int dummy; } ;
struct dm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int EINVAL ; 
 int create_log_context (struct dm_dirty_log*,struct dm_target*,unsigned int,char**,struct dm_dev*) ; 
 int dm_get_device (struct dm_target*,char*,int /*<<< orphan*/ ,struct dm_dev**) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,struct dm_dev*) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disk_ctr(struct dm_dirty_log *log, struct dm_target *ti,
		    unsigned int argc, char **argv)
{
	int r;
	struct dm_dev *dev;

	if (argc < 2 || argc > 3) {
		DMWARN("wrong number of arguments to disk dirty region log");
		return -EINVAL;
	}

	r = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &dev);
	if (r)
		return r;

	r = create_log_context(log, ti, argc - 1, argv + 1, dev);
	if (r) {
		dm_put_device(ti, dev);
		return r;
	}

	return 0;
}