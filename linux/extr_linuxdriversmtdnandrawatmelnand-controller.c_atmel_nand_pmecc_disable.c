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
struct atmel_nand {int /*<<< orphan*/  pmecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_pmecc_disable (int /*<<< orphan*/ ) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 

__attribute__((used)) static void atmel_nand_pmecc_disable(struct nand_chip *chip, bool raw)
{
	struct atmel_nand *nand = to_atmel_nand(chip);

	if (!raw)
		atmel_pmecc_disable(nand->pmecc);
}