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
struct fs_info_t {scalar_t__ dev_ejected; } ;
struct chain_t {int dir; int flags; int size; } ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 int CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_read (struct super_block*,int,int*) ; 

u32 find_last_cluster(struct super_block *sb, struct chain_t *p_chain)
{
	u32 clu, next;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	clu = p_chain->dir;

	if (p_chain->flags == 0x03) {
		clu += p_chain->size - 1;
	} else {
		while ((FAT_read(sb, clu, &next) == 0) &&
		       (next != CLUSTER_32(~0))) {
			if (p_fs->dev_ejected)
				break;
			clu = next;
		}
	}

	return clu;
}