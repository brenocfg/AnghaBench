#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
struct vol_info_t {scalar_t__ NumClusters; scalar_t__ UsedClusters; scalar_t__ FreeClusters; int /*<<< orphan*/  ClusterSize; int /*<<< orphan*/  FatType; } ;
struct super_block {int /*<<< orphan*/  s_magic; TYPE_1__* s_bdev; } ;
struct TYPE_5__ {void** val; } ;
struct kstatfs {scalar_t__ f_blocks; scalar_t__ f_bfree; scalar_t__ f_bavail; int f_namelen; TYPE_2__ f_fsid; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct fs_info_t {scalar_t__ used_clusters; scalar_t__ num_clusters; scalar_t__ dev_ejected; int /*<<< orphan*/  cluster_size; int /*<<< orphan*/  vol_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_6__ {struct fs_info_t fs_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_3__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FFS_MEDIAERR ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ ffsGetVolInfo (struct super_block*,struct vol_info_t*) ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int exfat_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct vol_info_t info;

	if (p_fs->used_clusters == UINT_MAX) {
		if (ffsGetVolInfo(sb, &info) == FFS_MEDIAERR)
			return -EIO;

	} else {
		info.FatType = p_fs->vol_type;
		info.ClusterSize = p_fs->cluster_size;
		info.NumClusters = p_fs->num_clusters - 2;
		info.UsedClusters = p_fs->used_clusters;
		info.FreeClusters = info.NumClusters - info.UsedClusters;

		if (p_fs->dev_ejected)
			pr_info("[EXFAT] statfs on device that is ejected\n");
	}

	buf->f_type = sb->s_magic;
	buf->f_bsize = info.ClusterSize;
	buf->f_blocks = info.NumClusters;
	buf->f_bfree = info.FreeClusters;
	buf->f_bavail = info.FreeClusters;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);
	buf->f_namelen = 260;

	return 0;
}