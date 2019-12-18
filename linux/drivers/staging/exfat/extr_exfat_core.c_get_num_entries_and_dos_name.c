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
struct uni_name_t {int dummy; } ;
struct super_block {int dummy; } ;
struct fs_info_t {scalar_t__ vol_type; TYPE_1__* fs_func; } ;
struct dos_name_t {int name_case; scalar_t__ name; } ;
struct chain_t {int dummy; } ;
typedef  int s32 ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {int (* calc_num_entries ) (struct uni_name_t*) ;} ;

/* Variables and functions */
 scalar_t__ EXFAT ; 
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 int FFS_INVALIDPATH ; 
 int FFS_SUCCESS ; 
 int fat_generate_dos_name (struct super_block*,struct chain_t*,struct dos_name_t*) ; 
 int /*<<< orphan*/  nls_uniname_to_dosname (struct super_block*,struct dos_name_t*,struct uni_name_t*,int*) ; 
 char** reserved_names ; 
 int /*<<< orphan*/  strncmp (void*,char*,int) ; 
 int stub1 (struct uni_name_t*) ; 

s32 get_num_entries_and_dos_name(struct super_block *sb, struct chain_t *p_dir,
				 struct uni_name_t *p_uniname, s32 *entries,
				 struct dos_name_t *p_dosname)
{
	s32 ret, num_entries;
	bool lossy = false;
	char **r;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	num_entries = p_fs->fs_func->calc_num_entries(p_uniname);
	if (num_entries == 0)
		return FFS_INVALIDPATH;

	if (p_fs->vol_type != EXFAT) {
		nls_uniname_to_dosname(sb, p_dosname, p_uniname, &lossy);

		if (lossy) {
			ret = fat_generate_dos_name(sb, p_dir, p_dosname);
			if (ret)
				return ret;
		} else {
			for (r = reserved_names; *r; r++) {
				if (!strncmp((void *)p_dosname->name, *r, 8))
					return FFS_INVALIDPATH;
			}

			if (p_dosname->name_case != 0xFF)
				num_entries = 1;
		}

		if (num_entries > 1)
			p_dosname->name_case = 0x0;
	}

	*entries = num_entries;

	return FFS_SUCCESS;
}