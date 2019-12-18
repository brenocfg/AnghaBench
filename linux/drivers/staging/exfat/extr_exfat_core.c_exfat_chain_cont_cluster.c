#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 scalar_t__ FAT_write (struct super_block*,scalar_t__,scalar_t__) ; 

void exfat_chain_cont_cluster(struct super_block *sb, u32 chain, s32 len)
{
	if (len == 0)
		return;

	while (len > 1) {
		if (FAT_write(sb, chain, chain + 1) < 0)
			break;
		chain++;
		len--;
	}
	FAT_write(sb, chain, CLUSTER_32(~0));
}