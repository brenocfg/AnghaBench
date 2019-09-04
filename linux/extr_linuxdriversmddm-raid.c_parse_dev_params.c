#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int persistent; int major_version; int /*<<< orphan*/  recovery_cp; scalar_t__ external; int /*<<< orphan*/  disks; } ;
struct TYPE_10__ {int /*<<< orphan*/  same_set; } ;
struct TYPE_11__ {TYPE_3__ rdev; scalar_t__ dev; } ;
struct raid_set {int raid_disks; TYPE_6__* ti; TYPE_5__ md; TYPE_4__ journal_dev; TYPE_2__* dev; } ;
struct dm_arg_set {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_13__ {char* error; int /*<<< orphan*/  table; } ;
struct TYPE_8__ {int raid_disk; int /*<<< orphan*/  flags; int /*<<< orphan*/  same_set; int /*<<< orphan*/  bdev; int /*<<< orphan*/  meta_bdev; int /*<<< orphan*/  recovery_offset; int /*<<< orphan*/  sb_page; TYPE_5__* mddev; scalar_t__ new_data_offset; scalar_t__ data_offset; } ;
struct TYPE_9__ {TYPE_1__ rdev; TYPE_7__* data_dev; TYPE_7__* meta_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int dm_get_device (TYPE_6__*,char const*,int /*<<< orphan*/ ,TYPE_7__**) ; 
 char* dm_shift_arg (struct dm_arg_set*) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_dev_params(struct raid_set *rs, struct dm_arg_set *as)
{
	int i;
	int rebuild = 0;
	int metadata_available = 0;
	int r = 0;
	const char *arg;

	/* Put off the number of raid devices argument to get to dev pairs */
	arg = dm_shift_arg(as);
	if (!arg)
		return -EINVAL;

	for (i = 0; i < rs->raid_disks; i++) {
		rs->dev[i].rdev.raid_disk = i;

		rs->dev[i].meta_dev = NULL;
		rs->dev[i].data_dev = NULL;

		/*
		 * There are no offsets initially.
		 * Out of place reshape will set them accordingly.
		 */
		rs->dev[i].rdev.data_offset = 0;
		rs->dev[i].rdev.new_data_offset = 0;
		rs->dev[i].rdev.mddev = &rs->md;

		arg = dm_shift_arg(as);
		if (!arg)
			return -EINVAL;

		if (strcmp(arg, "-")) {
			r = dm_get_device(rs->ti, arg, dm_table_get_mode(rs->ti->table),
					  &rs->dev[i].meta_dev);
			if (r) {
				rs->ti->error = "RAID metadata device lookup failure";
				return r;
			}

			rs->dev[i].rdev.sb_page = alloc_page(GFP_KERNEL);
			if (!rs->dev[i].rdev.sb_page) {
				rs->ti->error = "Failed to allocate superblock page";
				return -ENOMEM;
			}
		}

		arg = dm_shift_arg(as);
		if (!arg)
			return -EINVAL;

		if (!strcmp(arg, "-")) {
			if (!test_bit(In_sync, &rs->dev[i].rdev.flags) &&
			    (!rs->dev[i].rdev.recovery_offset)) {
				rs->ti->error = "Drive designated for rebuild not specified";
				return -EINVAL;
			}

			if (rs->dev[i].meta_dev) {
				rs->ti->error = "No data device supplied with metadata device";
				return -EINVAL;
			}

			continue;
		}

		r = dm_get_device(rs->ti, arg, dm_table_get_mode(rs->ti->table),
				  &rs->dev[i].data_dev);
		if (r) {
			rs->ti->error = "RAID device lookup failure";
			return r;
		}

		if (rs->dev[i].meta_dev) {
			metadata_available = 1;
			rs->dev[i].rdev.meta_bdev = rs->dev[i].meta_dev->bdev;
		}
		rs->dev[i].rdev.bdev = rs->dev[i].data_dev->bdev;
		list_add_tail(&rs->dev[i].rdev.same_set, &rs->md.disks);
		if (!test_bit(In_sync, &rs->dev[i].rdev.flags))
			rebuild++;
	}

	if (rs->journal_dev.dev)
		list_add_tail(&rs->journal_dev.rdev.same_set, &rs->md.disks);

	if (metadata_available) {
		rs->md.external = 0;
		rs->md.persistent = 1;
		rs->md.major_version = 2;
	} else if (rebuild && !rs->md.recovery_cp) {
		/*
		 * Without metadata, we will not be able to tell if the array
		 * is in-sync or not - we must assume it is not.  Therefore,
		 * it is impossible to rebuild a drive.
		 *
		 * Even if there is metadata, the on-disk information may
		 * indicate that the array is not in-sync and it will then
		 * fail at that time.
		 *
		 * User could specify 'nosync' option if desperate.
		 */
		rs->ti->error = "Unable to rebuild drive while array is not in-sync";
		return -EINVAL;
	}

	return 0;
}