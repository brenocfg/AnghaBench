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
typedef  int /*<<< orphan*/  u8 ;
struct uni_name_t {int dummy; } ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fs_info_t {int /*<<< orphan*/  v_sem; scalar_t__ dev_ejected; } ;
struct file_id_t {int dummy; } ;
struct chain_t {int dummy; } ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int FFS_ERROR ; 
 int FFS_MEDIAERR ; 
 int /*<<< orphan*/  VOL_CLEAN ; 
 int /*<<< orphan*/  VOL_DIRTY ; 
 int create_file (struct inode*,struct chain_t*,struct uni_name_t*,int /*<<< orphan*/ ,struct file_id_t*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_set_vol_flags (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_sync (struct super_block*,int) ; 
 int resolve_path (struct inode*,char*,struct chain_t*,struct uni_name_t*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffsCreateFile(struct inode *inode, char *path, u8 mode,
			 struct file_id_t *fid)
{
	struct chain_t dir;
	struct uni_name_t uni_name;
	struct super_block *sb = inode->i_sb;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	int ret;

	/* check the validity of pointer parameters */
	if (!fid || !path || (*path == '\0'))
		return FFS_ERROR;

	/* acquire the lock for file system critical section */
	down(&p_fs->v_sem);

	/* check the validity of directory name in the given pathname */
	ret = resolve_path(inode, path, &dir, &uni_name);
	if (ret)
		goto out;

	fs_set_vol_flags(sb, VOL_DIRTY);

	/* create a new file */
	ret = create_file(inode, &dir, &uni_name, mode, fid);

#ifdef CONFIG_EXFAT_DELAYED_SYNC
	fs_sync(sb, false);
	fs_set_vol_flags(sb, VOL_CLEAN);
#endif

	if (p_fs->dev_ejected)
		ret = FFS_MEDIAERR;

out:
	/* release the lock for file system critical section */
	up(&p_fs->v_sem);

	return ret;
}