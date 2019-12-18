#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct fs_info_t {scalar_t__ vol_type; int /*<<< orphan*/  v_sem; scalar_t__ dev_ejected; } ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 scalar_t__ EXFAT ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  FAT_release_all (struct super_block*) ; 
 int FFS_MEDIAERR ; 
 int FFS_SUCCESS ; 
 int /*<<< orphan*/  VOL_CLEAN ; 
 int /*<<< orphan*/  bdev_close (struct super_block*) ; 
 int /*<<< orphan*/  buf_release_all (struct super_block*) ; 
 int /*<<< orphan*/  buf_shutdown (struct super_block*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_alloc_bitmap (struct super_block*) ; 
 int /*<<< orphan*/  free_upcase_table (struct super_block*) ; 
 int /*<<< orphan*/  fs_set_vol_flags (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_sync (struct super_block*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z_sem ; 

__attribute__((used)) static int ffsUmountVol(struct super_block *sb)
{
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	int err = FFS_SUCCESS;

	pr_info("[EXFAT] trying to unmount...\n");

	down(&z_sem);

	/* acquire the lock for file system critical section */
	down(&p_fs->v_sem);

	fs_sync(sb, false);
	fs_set_vol_flags(sb, VOL_CLEAN);

	if (p_fs->vol_type == EXFAT) {
		free_upcase_table(sb);
		free_alloc_bitmap(sb);
	}

	FAT_release_all(sb);
	buf_release_all(sb);

	/* close the block device */
	bdev_close(sb);

	if (p_fs->dev_ejected) {
		pr_info("[EXFAT] unmounted with media errors. Device is already ejected.\n");
		err = FFS_MEDIAERR;
	}

	buf_shutdown(sb);

	/* release the lock for file system critical section */
	up(&p_fs->v_sem);
	up(&z_sem);

	pr_info("[EXFAT] unmounted successfully\n");

	return err;
}