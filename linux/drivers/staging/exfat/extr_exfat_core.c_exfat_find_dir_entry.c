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
typedef  int u16 ;
struct uni_name_t {int* name; scalar_t__ name_hash; scalar_t__ name_len; } ;
struct super_block {int dummy; } ;
struct strm_dentry_t {scalar_t__ name_len; int /*<<< orphan*/  name_hash; } ;
struct name_dentry_t {int dummy; } ;
struct TYPE_6__ {scalar_t__ dir; scalar_t__ size; int flags; } ;
struct TYPE_7__ {scalar_t__ dir; int entry; TYPE_2__ clu; } ;
struct fs_info_t {scalar_t__ root_dir; int dentries_in_root; int dentries_per_clu; TYPE_3__ hint_uentry; TYPE_1__* fs_func; scalar_t__ dev_ejected; } ;
struct file_dentry_t {int num_ext; } ;
struct dos_name_t {int dummy; } ;
struct dentry_t {int dummy; } ;
struct chain_t {scalar_t__ dir; scalar_t__ size; int flags; } ;
typedef  int s32 ;
struct TYPE_8__ {struct fs_info_t fs_info; } ;
struct TYPE_5__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_4__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_read (struct super_block*,scalar_t__,scalar_t__*) ; 
 scalar_t__ GET16_A (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_ALL ; 
 scalar_t__ TYPE_DELETED ; 
 scalar_t__ TYPE_DIR ; 
 scalar_t__ TYPE_EXTEND ; 
 scalar_t__ TYPE_FILE ; 
 scalar_t__ TYPE_STREAM ; 
 scalar_t__ TYPE_UNUSED ; 
 scalar_t__ UNI_CUR_DIR_NAME ; 
 scalar_t__ UNI_PAR_DIR_NAME ; 
 int extract_uni_name_from_name_entry (struct name_dentry_t*,int*,int) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nls_uniname_cmp (struct super_block*,int*,int*) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

s32 exfat_find_dir_entry(struct super_block *sb, struct chain_t *p_dir,
			 struct uni_name_t *p_uniname, s32 num_entries,
			 struct dos_name_t *p_dosname, u32 type)
{
	int i = 0, dentry = 0, num_ext_entries = 0, len, step;
	s32 order = 0;
	bool is_feasible_entry = false;
	s32 dentries_per_clu, num_empty = 0;
	u32 entry_type;
	u16 entry_uniname[16], *uniname = NULL, unichar;
	struct chain_t clu;
	struct dentry_t *ep;
	struct file_dentry_t *file_ep;
	struct strm_dentry_t *strm_ep;
	struct name_dentry_t *name_ep;
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
	clu.size = p_dir->size;
	clu.flags = p_dir->flags;

	p_fs->hint_uentry.dir = p_dir->dir;
	p_fs->hint_uentry.entry = -1;

	while (clu.dir != CLUSTER_32(~0)) {
		if (p_fs->dev_ejected)
			break;

		while (i < dentries_per_clu) {
			ep = get_entry_in_dir(sb, &clu, i, NULL);
			if (!ep)
				return -2;

			entry_type = p_fs->fs_func->get_entry_type(ep);
			step = 1;

			if ((entry_type == TYPE_UNUSED) || (entry_type == TYPE_DELETED)) {
				is_feasible_entry = false;

				if (p_fs->hint_uentry.entry == -1) {
					num_empty++;

					if (num_empty == 1) {
						p_fs->hint_uentry.clu.dir = clu.dir;
						p_fs->hint_uentry.clu.size = clu.size;
						p_fs->hint_uentry.clu.flags = clu.flags;
					}
					if ((num_empty >= num_entries) || (entry_type == TYPE_UNUSED))
						p_fs->hint_uentry.entry = dentry - (num_empty - 1);
				}

				if (entry_type == TYPE_UNUSED)
					return -2;
			} else {
				num_empty = 0;

				if ((entry_type == TYPE_FILE) || (entry_type == TYPE_DIR)) {
					file_ep = (struct file_dentry_t *)ep;
					if ((type == TYPE_ALL) || (type == entry_type)) {
						num_ext_entries = file_ep->num_ext;
						is_feasible_entry = true;
					} else {
						is_feasible_entry = false;
						step = file_ep->num_ext + 1;
					}
				} else if (entry_type == TYPE_STREAM) {
					if (is_feasible_entry) {
						strm_ep = (struct strm_dentry_t *)ep;
						if (p_uniname->name_hash == GET16_A(strm_ep->name_hash) &&
						    p_uniname->name_len == strm_ep->name_len) {
							order = 1;
						} else {
							is_feasible_entry = false;
							step = num_ext_entries;
						}
					}
				} else if (entry_type == TYPE_EXTEND) {
					if (is_feasible_entry) {
						name_ep = (struct name_dentry_t *)ep;

						if ((++order) == 2)
							uniname = p_uniname->name;
						else
							uniname += 15;

						len = extract_uni_name_from_name_entry(name_ep,
								entry_uniname, order);

						unichar = *(uniname + len);
						*(uniname + len) = 0x0;

						if (nls_uniname_cmp(sb, uniname, entry_uniname)) {
							is_feasible_entry = false;
							step = num_ext_entries - order + 1;
						} else if (order == num_ext_entries) {
							p_fs->hint_uentry.dir = CLUSTER_32(~0);
							p_fs->hint_uentry.entry = -1;
							return dentry - (num_ext_entries);
						}

						*(uniname + len) = unichar;
					}
				} else {
					is_feasible_entry = false;
				}
			}

			i += step;
			dentry += step;
		}

		i -= dentries_per_clu;

		if (p_dir->dir == CLUSTER_32(0))
			break; /* FAT16 root_dir */

		if (clu.flags == 0x03) {
			if ((--clu.size) > 0)
				clu.dir++;
			else
				clu.dir = CLUSTER_32(~0);
		} else {
			if (FAT_read(sb, clu.dir, &clu.dir) != 0)
				return -2;
		}
	}

	return -2;
}