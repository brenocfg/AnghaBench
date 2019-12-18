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

__attribute__((used)) static int esmt_nand_init(struct nand_chip *chip)
{
	if (nand_is_slc(chip))
		/*
		 * It is known that some ESMT SLC NANDs have been shipped
		 * with the factory bad block markers in the first or last page
		 * of the block, instead of the first or second page. To be on
		 * the safe side, let's check all three locations.
		 */
		chip->options |= NAND_BBM_FIRSTPAGE | NAND_BBM_SECONDPAGE |
				 NAND_BBM_LASTPAGE;

	return 0;
}