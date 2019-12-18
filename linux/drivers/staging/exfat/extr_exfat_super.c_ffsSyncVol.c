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
struct fs_info_t {int /*<<< orphan*/  v_sem; scalar_t__ dev_ejected; } ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int FFS_MEDIAERR ; 
 int FFS_SUCCESS ; 
 int /*<<< orphan*/  VOL_CLEAN ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_set_vol_flags (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_sync (struct super_block*,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffsSyncVol(struct super_block *sb, bool do_sync)
{
	int err = FFS_SUCCESS;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	/* acquire the lock for file system critical section */
	down(&p_fs->v_sem);

	/* synchronize the file system */
	fs_sync(sb, do_sync);
	fs_set_vol_flags(sb, VOL_CLEAN);

	if (p_fs->dev_ejected)
		err = FFS_MEDIAERR;

	/* release the lock for file system critical section */
	up(&p_fs->v_sem);

	return err;
}