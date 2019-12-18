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
struct fs_info_t {TYPE_1__* fs_func; } ;
struct file_dentry_t {int num_ext; } ;
struct dentry_t {int dummy; } ;
struct chain_t {int dummy; } ;
typedef  int s32 ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ TYPE_EXTEND ; 
 scalar_t__ TYPE_STREAM ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

s32 exfat_count_ext_entries(struct super_block *sb, struct chain_t *p_dir,
			    s32 entry, struct dentry_t *p_entry)
{
	int i, count = 0;
	u32 type;
	struct file_dentry_t *file_ep = (struct file_dentry_t *)p_entry;
	struct dentry_t *ext_ep;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	for (i = 0, entry++; i < file_ep->num_ext; i++, entry++) {
		ext_ep = get_entry_in_dir(sb, p_dir, entry, NULL);
		if (!ext_ep)
			return -1;

		type = p_fs->fs_func->get_entry_type(ext_ep);
		if ((type == TYPE_EXTEND) || (type == TYPE_STREAM))
			count++;
		else
			return count;
	}

	return count;
}