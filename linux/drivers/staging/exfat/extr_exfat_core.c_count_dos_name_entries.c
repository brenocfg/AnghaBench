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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct fs_info_t {int dentries_in_root; int dentries_per_clu; TYPE_1__* fs_func; scalar_t__ dev_ejected; } ;
struct dentry_t {int dummy; } ;
struct chain_t {scalar_t__ dir; scalar_t__ size; int flags; } ;
typedef  int s32 ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_read (struct super_block*,scalar_t__,scalar_t__*) ; 
 scalar_t__ TYPE_ALL ; 
 scalar_t__ TYPE_BENIGN_PRI ; 
 scalar_t__ TYPE_CRITICAL_PRI ; 
 scalar_t__ TYPE_UNUSED ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

s32 count_dos_name_entries(struct super_block *sb, struct chain_t *p_dir,
			   u32 type)
{
	int i, count = 0;
	s32 dentries_per_clu;
	u32 entry_type;
	struct chain_t clu;
	struct dentry_t *ep;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	if (p_dir->dir == CLUSTER_32(0)) /* FAT16 root_dir */
		dentries_per_clu = p_fs->dentries_in_root;
	else
		dentries_per_clu = p_fs->dentries_per_clu;

	clu.dir = p_dir->dir;
	clu.size = p_dir->size;
	clu.flags = p_dir->flags;

	while (clu.dir != CLUSTER_32(~0)) {
		if (p_fs->dev_ejected)
			break;

		for (i = 0; i < dentries_per_clu; i++) {
			ep = get_entry_in_dir(sb, &clu, i, NULL);
			if (!ep)
				return -1;

			entry_type = p_fs->fs_func->get_entry_type(ep);

			if (entry_type == TYPE_UNUSED)
				return count;
			if (!(type & TYPE_CRITICAL_PRI) &&
			    !(type & TYPE_BENIGN_PRI))
				continue;

			if ((type == TYPE_ALL) || (type == entry_type))
				count++;
		}

		if (p_dir->dir == CLUSTER_32(0))
			break; /* FAT16 root_dir */

		if (clu.flags == 0x03) {
			if ((--clu.size) > 0)
				clu.dir++;
			else
				clu.dir = CLUSTER_32(~0);
		} else {
			if (FAT_read(sb, clu.dir, &clu.dir) != 0)
				return -1;
		}
	}

	return count;
}