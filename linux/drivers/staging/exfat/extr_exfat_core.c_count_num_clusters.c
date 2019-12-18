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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct fs_info_t {int num_clusters; } ;
struct chain_t {scalar_t__ dir; int flags; int size; } ;
typedef  int s32 ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_read (struct super_block*,scalar_t__,scalar_t__*) ; 

s32 count_num_clusters(struct super_block *sb, struct chain_t *p_chain)
{
	int i, count = 0;
	u32 clu;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	if ((p_chain->dir == CLUSTER_32(0)) || (p_chain->dir == CLUSTER_32(~0)))
		return 0;

	clu = p_chain->dir;

	if (p_chain->flags == 0x03) {
		count = p_chain->size;
	} else {
		for (i = 2; i < p_fs->num_clusters; i++) {
			count++;
			if (FAT_read(sb, clu, &clu) != 0)
				return 0;
			if (clu == CLUSTER_32(~0))
				break;
		}
	}

	return count;
}