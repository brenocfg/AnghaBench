#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vol_info_t {scalar_t__ NumClusters; scalar_t__ UsedClusters; scalar_t__ FreeClusters; int /*<<< orphan*/  ClusterSize; int /*<<< orphan*/  FatType; } ;
struct super_block {int dummy; } ;
struct fs_info_t {scalar_t__ used_clusters; scalar_t__ num_clusters; int /*<<< orphan*/  v_sem; scalar_t__ dev_ejected; int /*<<< orphan*/  cluster_size; int /*<<< orphan*/  vol_type; TYPE_1__* fs_func; } ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ (* count_used_clusters ) (struct super_block*) ;} ;

/* Variables and functions */
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 int FFS_ERROR ; 
 int FFS_MEDIAERR ; 
 int FFS_SUCCESS ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct super_block*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffsGetVolInfo(struct super_block *sb, struct vol_info_t *info)
{
	int err = FFS_SUCCESS;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	/* check the validity of pointer parameters */
	if (!info)
		return FFS_ERROR;

	/* acquire the lock for file system critical section */
	down(&p_fs->v_sem);

	if (p_fs->used_clusters == UINT_MAX)
		p_fs->used_clusters = p_fs->fs_func->count_used_clusters(sb);

	info->FatType = p_fs->vol_type;
	info->ClusterSize = p_fs->cluster_size;
	info->NumClusters = p_fs->num_clusters - 2; /* clu 0 & 1 */
	info->UsedClusters = p_fs->used_clusters;
	info->FreeClusters = info->NumClusters - info->UsedClusters;

	if (p_fs->dev_ejected)
		err = FFS_MEDIAERR;

	/* release the lock for file system critical section */
	up(&p_fs->v_sem);

	return err;
}