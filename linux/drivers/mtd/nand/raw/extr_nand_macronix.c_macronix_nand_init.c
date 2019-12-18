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
 int NAND_BBM_SECONDPAGE ; 
 int /*<<< orphan*/  macronix_nand_fix_broken_get_timings (struct nand_chip*) ; 
 int /*<<< orphan*/  macronix_nand_onfi_init (struct nand_chip*) ; 
 scalar_t__ nand_is_slc (struct nand_chip*) ; 

__attribute__((used)) static int macronix_nand_init(struct nand_chip *chip)
{
	if (nand_is_slc(chip))
		chip->options |= NAND_BBM_FIRSTPAGE | NAND_BBM_SECONDPAGE;

	macronix_nand_fix_broken_get_timings(chip);
	macronix_nand_onfi_init(chip);

	return 0;
}