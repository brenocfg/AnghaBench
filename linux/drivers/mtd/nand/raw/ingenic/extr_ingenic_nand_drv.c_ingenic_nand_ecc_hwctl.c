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
struct nand_chip {int dummy; } ;
struct ingenic_nand {int reading; } ;

/* Variables and functions */
 int NAND_ECC_READ ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 struct ingenic_nand* to_ingenic_nand (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ingenic_nand_ecc_hwctl(struct nand_chip *chip, int mode)
{
	struct ingenic_nand *nand = to_ingenic_nand(nand_to_mtd(chip));

	nand->reading = (mode == NAND_ECC_READ);
}