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
typedef  scalar_t__ u8 ;
struct super_block {int dummy; } ;
struct fs_info_t {TYPE_1__* fs_func; } ;
struct ext_dentry_t {scalar_t__ checksum; int order; } ;
struct dos_dentry_t {scalar_t__ name; } ;
struct dentry_t {int dummy; } ;
struct chain_t {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DOS_NAME_LENGTH ; 
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ TYPE_EXTEND ; 
 scalar_t__ calc_checksum_1byte (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_entry_in_dir (struct super_block*,struct chain_t*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

s32 fat_count_ext_entries(struct super_block *sb, struct chain_t *p_dir,
			  s32 entry, struct dentry_t *p_entry)
{
	s32 count = 0;
	u8 chksum;
	struct dos_dentry_t *dos_ep = (struct dos_dentry_t *)p_entry;
	struct ext_dentry_t *ext_ep;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	chksum = calc_checksum_1byte((void *)dos_ep->name, DOS_NAME_LENGTH, 0);

	for (entry--; entry >= 0; entry--) {
		ext_ep = (struct ext_dentry_t *)get_entry_in_dir(sb, p_dir,
								 entry, NULL);
		if (!ext_ep)
			return -1;

		if ((p_fs->fs_func->get_entry_type((struct dentry_t *)ext_ep) ==
		     TYPE_EXTEND) && (ext_ep->checksum == chksum)) {
			count++;
			if (ext_ep->order > 0x40)
				return count;
		} else {
			return count;
		}
	}

	return count;
}