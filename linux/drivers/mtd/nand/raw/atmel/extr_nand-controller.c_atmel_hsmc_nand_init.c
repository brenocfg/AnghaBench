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
struct TYPE_2__ {int /*<<< orphan*/  select_chip; int /*<<< orphan*/  cmd_ctrl; } ;
struct nand_chip {TYPE_1__ legacy; } ;
struct atmel_nand_controller {int dummy; } ;
struct atmel_nand {struct nand_chip base; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_hsmc_nand_cmd_ctrl ; 
 int /*<<< orphan*/  atmel_hsmc_nand_select_chip ; 
 int /*<<< orphan*/  atmel_nand_init (struct atmel_nand_controller*,struct atmel_nand*) ; 

__attribute__((used)) static void atmel_hsmc_nand_init(struct atmel_nand_controller *nc,
				 struct atmel_nand *nand)
{
	struct nand_chip *chip = &nand->base;

	atmel_nand_init(nc, nand);

	/* Overload some methods for the HSMC controller. */
	chip->legacy.cmd_ctrl = atmel_hsmc_nand_cmd_ctrl;
	chip->legacy.select_chip = atmel_hsmc_nand_select_chip;
}