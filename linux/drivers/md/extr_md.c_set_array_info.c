#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int default_offset; int default_space; scalar_t__ offset; } ;
struct mddev {size_t major_version; int persistent; scalar_t__ level; int dev_sectors; scalar_t__ raid_disks; int layout; int chunk_sectors; scalar_t__ new_level; int new_chunk_sectors; int new_layout; scalar_t__ reshape_backwards; scalar_t__ delta_disks; int /*<<< orphan*/  uuid; void* reshape_position; TYPE_1__ bitmap_info; scalar_t__ sb_flags; scalar_t__ flags; int /*<<< orphan*/  max_disks; scalar_t__ external; void* recovery_cp; scalar_t__* clevel; void* ctime; int /*<<< orphan*/  patch_version; int /*<<< orphan*/  minor_version; } ;
typedef  int sector_t ;
struct TYPE_7__ {scalar_t__ raid_disks; size_t major_version; scalar_t__ level; int state; int layout; int chunk_size; int /*<<< orphan*/  not_persistent; scalar_t__ size; int /*<<< orphan*/  patch_version; int /*<<< orphan*/  minor_version; } ;
typedef  TYPE_2__ mdu_array_info_t ;
struct TYPE_8__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 size_t MD_MAJOR_VERSION ; 
 int /*<<< orphan*/  MD_MINOR_VERSION ; 
 int /*<<< orphan*/  MD_PATCHLEVEL_VERSION ; 
 int MD_SB_BYTES ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int MD_SB_CLEAN ; 
 int /*<<< orphan*/  MD_SB_DISKS ; 
 void* MaxSector ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 void* ktime_get_real_seconds () ; 
 int /*<<< orphan*/  pr_warn (char*,size_t) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_3__* super_types ; 

__attribute__((used)) static int set_array_info(struct mddev *mddev, mdu_array_info_t *info)
{

	if (info->raid_disks == 0) {
		/* just setting version number for superblock loading */
		if (info->major_version < 0 ||
		    info->major_version >= ARRAY_SIZE(super_types) ||
		    super_types[info->major_version].name == NULL) {
			/* maybe try to auto-load a module? */
			pr_warn("md: superblock version %d not known\n",
				info->major_version);
			return -EINVAL;
		}
		mddev->major_version = info->major_version;
		mddev->minor_version = info->minor_version;
		mddev->patch_version = info->patch_version;
		mddev->persistent = !info->not_persistent;
		/* ensure mddev_put doesn't delete this now that there
		 * is some minimal configuration.
		 */
		mddev->ctime         = ktime_get_real_seconds();
		return 0;
	}
	mddev->major_version = MD_MAJOR_VERSION;
	mddev->minor_version = MD_MINOR_VERSION;
	mddev->patch_version = MD_PATCHLEVEL_VERSION;
	mddev->ctime         = ktime_get_real_seconds();

	mddev->level         = info->level;
	mddev->clevel[0]     = 0;
	mddev->dev_sectors   = 2 * (sector_t)info->size;
	mddev->raid_disks    = info->raid_disks;
	/* don't set md_minor, it is determined by which /dev/md* was
	 * openned
	 */
	if (info->state & (1<<MD_SB_CLEAN))
		mddev->recovery_cp = MaxSector;
	else
		mddev->recovery_cp = 0;
	mddev->persistent    = ! info->not_persistent;
	mddev->external	     = 0;

	mddev->layout        = info->layout;
	if (mddev->level == 0)
		/* Cannot trust RAID0 layout info here */
		mddev->layout = -1;
	mddev->chunk_sectors = info->chunk_size >> 9;

	if (mddev->persistent) {
		mddev->max_disks = MD_SB_DISKS;
		mddev->flags = 0;
		mddev->sb_flags = 0;
	}
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);

	mddev->bitmap_info.default_offset = MD_SB_BYTES >> 9;
	mddev->bitmap_info.default_space = 64*2 - (MD_SB_BYTES >> 9);
	mddev->bitmap_info.offset = 0;

	mddev->reshape_position = MaxSector;

	/*
	 * Generate a 128 bit UUID
	 */
	get_random_bytes(mddev->uuid, 16);

	mddev->new_level = mddev->level;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
	mddev->new_layout = mddev->layout;
	mddev->delta_disks = 0;
	mddev->reshape_backwards = 0;

	return 0;
}