#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct TYPE_6__ {scalar_t__ dir; scalar_t__ size; int flags; } ;
struct TYPE_7__ {scalar_t__ dir; int entry; TYPE_2__ clu; } ;
struct fs_info_t {int dentries_in_root; int dentries_per_clu; scalar_t__ vol_type; TYPE_3__ hint_uentry; TYPE_1__* fs_func; scalar_t__ dev_ejected; } ;
struct dentry_t {int dummy; } ;
struct chain_t {scalar_t__ dir; scalar_t__ size; int flags; } ;
typedef  int s32 ;
struct TYPE_8__ {struct fs_info_t fs_info; } ;
struct TYPE_5__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 scalar_t__ EXFAT ; 
 TYPE_4__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_read (struct super_block*,scalar_t__,scalar_t__*) ; 
 scalar_t__ TYPE_DELETED ; 
 scalar_t__ TYPE_UNUSED ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

s32 search_deleted_or_unused_entry(struct super_block *sb,
				   struct chain_t *p_dir, s32 num_entries)
{
	int i, dentry, num_empty = 0;
	s32 dentries_per_clu;
	u32 type;
	struct chain_t clu;
	struct dentry_t *ep;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	if (p_dir->dir == CLUSTER_32(0)) /* FAT16 root_dir */
		dentries_per_clu = p_fs->dentries_in_root;
	else
		dentries_per_clu = p_fs->dentries_per_clu;

	if (p_fs->hint_uentry.dir == p_dir->dir) {
		if (p_fs->hint_uentry.entry == -1)
			return -1;

		clu.dir = p_fs->hint_uentry.clu.dir;
		clu.size = p_fs->hint_uentry.clu.size;
		clu.flags = p_fs->hint_uentry.clu.flags;

		dentry = p_fs->hint_uentry.entry;
	} else {
		p_fs->hint_uentry.entry = -1;

		clu.dir = p_dir->dir;
		clu.size = p_dir->size;
		clu.flags = p_dir->flags;

		dentry = 0;
	}

	while (clu.dir != CLUSTER_32(~0)) {
		if (p_fs->dev_ejected)
			break;

		if (p_dir->dir == CLUSTER_32(0)) /* FAT16 root_dir */
			i = dentry % dentries_per_clu;
		else
			i = dentry & (dentries_per_clu - 1);

		for (; i < dentries_per_clu; i++, dentry++) {
			ep = get_entry_in_dir(sb, &clu, i, NULL);
			if (!ep)
				return -1;

			type = p_fs->fs_func->get_entry_type(ep);

			if (type == TYPE_UNUSED) {
				num_empty++;
				if (p_fs->hint_uentry.entry == -1) {
					p_fs->hint_uentry.dir = p_dir->dir;
					p_fs->hint_uentry.entry = dentry;

					p_fs->hint_uentry.clu.dir = clu.dir;
					p_fs->hint_uentry.clu.size = clu.size;
					p_fs->hint_uentry.clu.flags = clu.flags;
				}
			} else if (type == TYPE_DELETED) {
				num_empty++;
			} else {
				num_empty = 0;
			}

			if (num_empty >= num_entries) {
				p_fs->hint_uentry.dir = CLUSTER_32(~0);
				p_fs->hint_uentry.entry = -1;

				if (p_fs->vol_type == EXFAT)
					return dentry - (num_entries - 1);
				else
					return dentry;
			}
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

	return -1;
}