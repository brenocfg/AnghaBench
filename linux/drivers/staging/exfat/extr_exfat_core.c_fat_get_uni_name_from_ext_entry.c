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
typedef  int /*<<< orphan*/  u16 ;
struct super_block {int dummy; } ;
struct fs_info_t {TYPE_1__* fs_func; } ;
struct ext_dentry_t {int order; } ;
struct dentry_t {int dummy; } ;
struct chain_t {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ TYPE_EXTEND ; 
 int /*<<< orphan*/  extract_uni_name_from_ext_entry (struct ext_dentry_t*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_entry_in_dir (struct super_block*,struct chain_t*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

void fat_get_uni_name_from_ext_entry(struct super_block *sb,
				     struct chain_t *p_dir, s32 entry,
				     u16 *uniname)
{
	int i;
	struct ext_dentry_t *ep;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	for (entry--, i = 1; entry >= 0; entry--, i++) {
		ep = (struct ext_dentry_t *)get_entry_in_dir(sb, p_dir, entry,
							     NULL);
		if (!ep)
			return;

		if (p_fs->fs_func->get_entry_type((struct dentry_t *)ep) ==
		    TYPE_EXTEND) {
			extract_uni_name_from_ext_entry(ep, uniname, i);
			if (ep->order > 0x40)
				return;
		} else {
			return;
		}

		uniname += 13;
	}
}