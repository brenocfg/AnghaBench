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
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int NAND_BBM_FIRSTPAGE ; 
 int NAND_BBM_LASTPAGE ; 
 int NAND_BBM_SECONDPAGE ; 
 int NAND_SAMSUNG_LP_OPTIONS ; 
 int /*<<< orphan*/  nand_is_slc (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int samsung_nand_init(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (mtd->writesize > 512)
		chip->options |= NAND_SAMSUNG_LP_OPTIONS;

	if (!nand_is_slc(chip))
		chip->options |= NAND_BBM_LASTPAGE;
	else
		chip->options |= NAND_BBM_FIRSTPAGE | NAND_BBM_SECONDPAGE;

	return 0;
}