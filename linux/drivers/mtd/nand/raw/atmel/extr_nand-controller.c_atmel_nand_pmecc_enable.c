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
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct atmel_nand_controller {int /*<<< orphan*/  dev; } ;
struct atmel_nand {int /*<<< orphan*/  pmecc; } ;

/* Variables and functions */
 int atmel_pmecc_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 
 struct atmel_nand_controller* to_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_nand_pmecc_enable(struct nand_chip *chip, int op, bool raw)
{
	struct atmel_nand *nand = to_atmel_nand(chip);
	struct atmel_nand_controller *nc;
	int ret;

	nc = to_nand_controller(chip->controller);

	if (raw)
		return 0;

	ret = atmel_pmecc_enable(nand->pmecc, op);
	if (ret)
		dev_err(nc->dev,
			"Failed to enable ECC engine (err = %d)\n", ret);

	return ret;
}