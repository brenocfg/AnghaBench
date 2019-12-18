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
struct name_dentry_t {int dummy; } ;
struct fs_info_t {TYPE_1__* fs_func; } ;
struct entry_set_cache_t {int num_entries; } ;
struct dentry_t {int dummy; } ;
struct chain_t {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ES_ALL_ENTRIES ; 
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ TYPE_EXTEND ; 
 int /*<<< orphan*/  extract_uni_name_from_name_entry (struct name_dentry_t*,int /*<<< orphan*/ *,int) ; 
 struct entry_set_cache_t* get_entry_set_in_dir (struct super_block*,struct chain_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry_t**) ; 
 int /*<<< orphan*/  release_entry_set (struct entry_set_cache_t*) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

void exfat_get_uni_name_from_ext_entry(struct super_block *sb,
				       struct chain_t *p_dir, s32 entry,
				       u16 *uniname)
{
	int i;
	struct dentry_t *ep;
	struct entry_set_cache_t *es;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	es = get_entry_set_in_dir(sb, p_dir, entry, ES_ALL_ENTRIES, &ep);
	if (!es || es->num_entries < 3) {
		if (es)
			release_entry_set(es);
		return;
	}

	ep += 2;

	/*
	 * First entry  : file entry
	 * Second entry : stream-extension entry
	 * Third entry  : first file-name entry
	 * So, the index of first file-name dentry should start from 2.
	 */
	for (i = 2; i < es->num_entries; i++, ep++) {
		if (p_fs->fs_func->get_entry_type(ep) == TYPE_EXTEND)
			extract_uni_name_from_name_entry((struct name_dentry_t *)
							 ep, uniname, i);
		else
			goto out;
		uniname += 15;
	}

out:
	release_entry_set(es);
}