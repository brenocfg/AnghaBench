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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fs_info_t {int cluster_size_bits; int cluster_size; } ;
struct TYPE_4__ {scalar_t__ flags; int size; scalar_t__ dir; } ;
struct file_id_t {scalar_t__ flags; int size; scalar_t__ start_clu; TYPE_1__ dir; } ;
struct TYPE_6__ {struct file_id_t fid; } ;
struct TYPE_5__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_3__* EXFAT_I (struct inode*) ; 
 TYPE_2__* EXFAT_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void update_parent_info(struct file_id_t *fid,
			       struct inode *parent_inode)
{
	struct fs_info_t *p_fs = &(EXFAT_SB(parent_inode->i_sb)->fs_info);
	struct file_id_t *parent_fid = &(EXFAT_I(parent_inode)->fid);

	if (unlikely((parent_fid->flags != fid->dir.flags) ||
		     (parent_fid->size !=
		      (fid->dir.size << p_fs->cluster_size_bits)) ||
		     (parent_fid->start_clu != fid->dir.dir))) {
		fid->dir.dir = parent_fid->start_clu;
		fid->dir.flags = parent_fid->flags;
		fid->dir.size = ((parent_fid->size + (p_fs->cluster_size - 1))
						>> p_fs->cluster_size_bits);
	}
}