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
struct fs_info_t {int clu_srch_ptr; int num_clusters; scalar_t__ used_clusters; } ;
struct chain_t {int dir; int flags; int /*<<< orphan*/  size; } ;
typedef  int s32 ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 int CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_write (struct super_block*,int,int) ; 
 scalar_t__ FFS_SUCCESS ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  __set_sb_dirty (struct super_block*) ; 
 int /*<<< orphan*/  exfat_chain_cont_cluster (struct super_block*,int,int) ; 
 scalar_t__ set_alloc_bitmap (struct super_block*,int) ; 
 int test_alloc_bitmap (struct super_block*,int) ; 

s32 exfat_alloc_cluster(struct super_block *sb, s32 num_alloc,
			struct chain_t *p_chain)
{
	s32 num_clusters = 0;
	u32 hint_clu, new_clu, last_clu = CLUSTER_32(~0);
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	hint_clu = p_chain->dir;
	if (hint_clu == CLUSTER_32(~0)) {
		hint_clu = test_alloc_bitmap(sb, p_fs->clu_srch_ptr - 2);
		if (hint_clu == CLUSTER_32(~0))
			return 0;
	} else if (hint_clu >= p_fs->num_clusters) {
		hint_clu = 2;
		p_chain->flags = 0x01;
	}

	__set_sb_dirty(sb);

	p_chain->dir = CLUSTER_32(~0);

	while ((new_clu = test_alloc_bitmap(sb, hint_clu - 2)) != CLUSTER_32(~0)) {
		if (new_clu != hint_clu) {
			if (p_chain->flags == 0x03) {
				exfat_chain_cont_cluster(sb, p_chain->dir,
							 num_clusters);
				p_chain->flags = 0x01;
			}
		}

		if (set_alloc_bitmap(sb, new_clu - 2) != FFS_SUCCESS)
			return -1;

		num_clusters++;

		if (p_chain->flags == 0x01) {
			if (FAT_write(sb, new_clu, CLUSTER_32(~0)) < 0)
				return -1;
		}

		if (p_chain->dir == CLUSTER_32(~0)) {
			p_chain->dir = new_clu;
		} else {
			if (p_chain->flags == 0x01) {
				if (FAT_write(sb, last_clu, new_clu) < 0)
					return -1;
			}
		}
		last_clu = new_clu;

		if ((--num_alloc) == 0) {
			p_fs->clu_srch_ptr = hint_clu;
			if (p_fs->used_clusters != UINT_MAX)
				p_fs->used_clusters += num_clusters;

			p_chain->size += num_clusters;
			return num_clusters;
		}

		hint_clu = new_clu + 1;
		if (hint_clu >= p_fs->num_clusters) {
			hint_clu = 2;

			if (p_chain->flags == 0x03) {
				exfat_chain_cont_cluster(sb, p_chain->dir,
							 num_clusters);
				p_chain->flags = 0x01;
			}
		}
	}

	p_fs->clu_srch_ptr = hint_clu;
	if (p_fs->used_clusters != UINT_MAX)
		p_fs->used_clusters += num_clusters;

	p_chain->size += num_clusters;
	return num_clusters;
}