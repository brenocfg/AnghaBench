#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct super_block {int dummy; } ;
struct fs_info_t {int cluster_size_bits; } ;
struct chain_t {int dir; int flags; } ;
typedef  int s32 ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int FAT_read (struct super_block*,int,int*) ; 
 int FFS_MEDIAERR ; 
 int FFS_SUCCESS ; 

__attribute__((used)) static s32 _walk_fat_chain(struct super_block *sb, struct chain_t *p_dir,
			   s32 byte_offset, u32 *clu)
{
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	s32 clu_offset;
	u32 cur_clu;

	clu_offset = byte_offset >> p_fs->cluster_size_bits;
	cur_clu = p_dir->dir;

	if (p_dir->flags == 0x03) {
		cur_clu += clu_offset;
	} else {
		while (clu_offset > 0) {
			if (FAT_read(sb, cur_clu, &cur_clu) == -1)
				return FFS_MEDIAERR;
			clu_offset--;
		}
	}

	if (clu)
		*clu = cur_clu;
	return FFS_SUCCESS;
}