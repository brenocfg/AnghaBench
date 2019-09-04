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
typedef  int u32 ;
struct nand_chip {int max_bb_per_die; int blocks_per_die; } ;
struct mtd_info {int dummy; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int ENOTSUPP ; 
 int mtd_div_by_eb (size_t,struct mtd_info*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static int nand_max_bad_blocks(struct mtd_info *mtd, loff_t ofs, size_t len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	u32 part_start_block;
	u32 part_end_block;
	u32 part_start_die;
	u32 part_end_die;

	/*
	 * max_bb_per_die and blocks_per_die used to determine
	 * the maximum bad block count.
	 */
	if (!chip->max_bb_per_die || !chip->blocks_per_die)
		return -ENOTSUPP;

	/* Get the start and end of the partition in erase blocks. */
	part_start_block = mtd_div_by_eb(ofs, mtd);
	part_end_block = mtd_div_by_eb(len, mtd) + part_start_block - 1;

	/* Get the start and end LUNs of the partition. */
	part_start_die = part_start_block / chip->blocks_per_die;
	part_end_die = part_end_block / chip->blocks_per_die;

	/*
	 * Look up the bad blocks per unit and multiply by the number of units
	 * that the partition spans.
	 */
	return chip->max_bb_per_die * (part_end_die - part_start_die + 1);
}