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
struct super_block {int dummy; } ;
struct fs_info_t {TYPE_1__* fs_func; } ;
struct dentry_t {int dummy; } ;
struct chain_t {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int s32 ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_entry_type ) (struct dentry_t*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  TYPE_DELETED ; 
 int /*<<< orphan*/  buf_modify (struct super_block*,int /*<<< orphan*/ ) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dentry_t*,int /*<<< orphan*/ ) ; 

void exfat_delete_dir_entry(struct super_block *sb, struct chain_t *p_dir,
		s32 entry, s32 order, s32 num_entries)
{
	int i;
	sector_t sector;
	struct dentry_t *ep;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	for (i = order; i < num_entries; i++) {
		ep = get_entry_in_dir(sb, p_dir, entry + i, &sector);
		if (!ep)
			return;

		p_fs->fs_func->set_entry_type(ep, TYPE_DELETED);
		buf_modify(sb, sector);
	}
}