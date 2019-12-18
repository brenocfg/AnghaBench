#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct atmel_nand {TYPE_3__* activecs; } ;
struct TYPE_4__ {int /*<<< orphan*/  smc; } ;
struct atmel_hsmc_nand_controller {TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_2__ rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HSMC_NFC_SR ; 
 int ATMEL_HSMC_NFC_SR_RBEDGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 
 struct atmel_hsmc_nand_controller* to_hsmc_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_hsmc_nand_dev_ready(struct nand_chip *chip)
{
	struct atmel_nand *nand = to_atmel_nand(chip);
	struct atmel_hsmc_nand_controller *nc;
	u32 status;

	nc = to_hsmc_nand_controller(chip->controller);

	regmap_read(nc->base.smc, ATMEL_HSMC_NFC_SR, &status);

	return status & ATMEL_HSMC_NFC_SR_RBEDGE(nand->activecs->rb.id);
}