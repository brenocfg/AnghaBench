#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* data; } ;
struct TYPE_3__ {scalar_t__ mode; } ;
struct nand_chip {int options; TYPE_2__ id; TYPE_1__ ecc; } ;

/* Variables and functions */
 int NAND_BBM_FIRSTPAGE ; 
 int NAND_BBM_SECONDPAGE ; 
 scalar_t__ NAND_ECC_ON_DIE ; 
 int TOSHIBA_NAND_ID4_IS_BENAND ; 
 scalar_t__ nand_is_slc (struct nand_chip*) ; 
 int /*<<< orphan*/  toshiba_nand_benand_init (struct nand_chip*) ; 

__attribute__((used)) static int toshiba_nand_init(struct nand_chip *chip)
{
	if (nand_is_slc(chip))
		chip->options |= NAND_BBM_FIRSTPAGE | NAND_BBM_SECONDPAGE;

	/* Check that chip is BENAND and ECC mode is on-die */
	if (nand_is_slc(chip) && chip->ecc.mode == NAND_ECC_ON_DIE &&
	    chip->id.data[4] & TOSHIBA_NAND_ID4_IS_BENAND)
		toshiba_nand_benand_init(chip);

	return 0;
}