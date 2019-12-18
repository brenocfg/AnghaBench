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
struct nand_chip {int options; } ;

/* Variables and functions */
 int NAND_BBM_FIRSTPAGE ; 
 int NAND_BBM_LASTPAGE ; 
 int NAND_BBM_SECONDPAGE ; 
 scalar_t__ nand_is_slc (struct nand_chip*) ; 

__attribute__((used)) static int amd_nand_init(struct nand_chip *chip)
{
	if (nand_is_slc(chip))
		/*
		 * According to the datasheet of some Cypress SLC NANDs,
		 * the bad block markers can be in the first, second or last
		 * page of a block. So let's check all three locations.
		 */
		chip->options |= NAND_BBM_FIRSTPAGE | NAND_BBM_SECONDPAGE |
				 NAND_BBM_LASTPAGE;

	return 0;
}