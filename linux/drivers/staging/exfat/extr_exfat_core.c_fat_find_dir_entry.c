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
typedef  int u16 ;
struct uni_name_t {int* name; } ;
struct super_block {int dummy; } ;
struct fs_info_t {scalar_t__ root_dir; int dentries_in_root; int dentries_per_clu; TYPE_1__* fs_func; scalar_t__ dev_ejected; } ;
struct ext_dentry_t {int order; } ;
struct dos_name_t {int /*<<< orphan*/  name; } ;
struct dos_dentry_t {int /*<<< orphan*/  name; } ;
struct dentry_t {int dummy; } ;
struct chain_t {scalar_t__ dir; int /*<<< orphan*/  flags; } ;
typedef  int s32 ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_read (struct super_block*,scalar_t__,scalar_t__*) ; 
 scalar_t__ TYPE_ALL ; 
 scalar_t__ TYPE_DIR ; 
 scalar_t__ TYPE_EXTEND ; 
 scalar_t__ TYPE_FILE ; 
 scalar_t__ TYPE_UNUSED ; 
 scalar_t__ UNI_CUR_DIR_NAME ; 
 scalar_t__ UNI_PAR_DIR_NAME ; 
 int extract_uni_name_from_ext_entry (struct ext_dentry_t*,int*,int) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nls_dosname_cmp (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nls_uniname_cmp (struct super_block*,int*,int*) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

s32 fat_find_dir_entry(struct super_block *sb, struct chain_t *p_dir,
		       struct uni_name_t *p_uniname, s32 num_entries,
		       struct dos_name_t *p_dosname, u32 type)
{
	int i, dentry = 0, len;
	s32 order = 0;
	bool is_feasible_entry = true, has_ext_entry = false;
	s32 dentries_per_clu;
	u32 entry_type;
	u16 entry_uniname[14], *uniname = NULL, unichar;
	struct chain_t clu;
	struct dentry_t *ep;
	struct dos_dentry_t *dos_ep;
	struct ext_dentry_t *ext_ep;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	if (p_dir->dir == p_fs->root_dir) {
		if ((!nls_uniname_cmp(sb, p_uniname->name,
				      (u16 *)UNI_CUR_DIR_NAME)) ||
			(!nls_uniname_cmp(sb, p_uniname->name,
					  (u16 *)UNI_PAR_DIR_NAME)))
			return -1; // special case, root directory itself
	}

	if (p_dir->dir == CLUSTER_32(0)) /* FAT16 root_dir */
		dentries_per_clu = p_fs->dentries_in_root;
	else
		dentries_per_clu = p_fs->dentries_per_clu;

	clu.dir = p_dir->dir;
	clu.flags = p_dir->flags;

	while (clu.dir != CLUSTER_32(~0)) {
		if (p_fs->dev_ejected)
			break;

		for (i = 0; i < dentries_per_clu; i++, dentry++) {
			ep = get_entry_in_dir(sb, &clu, i, NULL);
			if (!ep)
				return -2;

			entry_type = p_fs->fs_func->get_entry_type(ep);

			if ((entry_type == TYPE_FILE) || (entry_type == TYPE_DIR)) {
				if ((type == TYPE_ALL) || (type == entry_type)) {
					if (is_feasible_entry && has_ext_entry)
						return dentry;

					dos_ep = (struct dos_dentry_t *)ep;
					if (!nls_dosname_cmp(sb, p_dosname->name, dos_ep->name))
						return dentry;
				}
				is_feasible_entry = true;
				has_ext_entry = false;
			} else if (entry_type == TYPE_EXTEND) {
				if (is_feasible_entry) {
					ext_ep = (struct ext_dentry_t *)ep;
					if (ext_ep->order > 0x40) {
						order = (s32)(ext_ep->order - 0x40);
						uniname = p_uniname->name + 13 * (order - 1);
					} else {
						order = (s32)ext_ep->order;
						uniname -= 13;
					}

					len = extract_uni_name_from_ext_entry(ext_ep, entry_uniname, order);

					unichar = *(uniname + len);
					*(uniname + len) = 0x0;

					if (nls_uniname_cmp(sb, uniname, entry_uniname))
						is_feasible_entry = false;

					*(uniname + len) = unichar;
				}
				has_ext_entry = true;
			} else if (entry_type == TYPE_UNUSED) {
				return -2;
			}
			is_feasible_entry = true;
			has_ext_entry = false;
		}

		if (p_dir->dir == CLUSTER_32(0))
			break; /* FAT16 root_dir */

		if (FAT_read(sb, clu.dir, &clu.dir) != 0)
			return -2;
	}

	return -2;
}