#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mode; } ;
struct nand_chip {int chip_delay; TYPE_4__ ecc; int /*<<< orphan*/  options; int /*<<< orphan*/  setup_data_interface; int /*<<< orphan*/  select_chip; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  write_byte; int /*<<< orphan*/  read_word; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/ * controller; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct mtd_info {TYPE_1__ dev; } ;
struct atmel_nand_controller {scalar_t__ pmecc; scalar_t__ dmac; TYPE_3__* caps; scalar_t__ mck; int /*<<< orphan*/  base; int /*<<< orphan*/  dev; } ;
struct atmel_nand {struct nand_chip base; } ;
struct TYPE_7__ {TYPE_2__* ops; } ;
struct TYPE_6__ {scalar_t__ setup_data_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int /*<<< orphan*/  NAND_USE_BOUNCE_BUFFER ; 
 int /*<<< orphan*/  atmel_nand_cmd_ctrl ; 
 int /*<<< orphan*/  atmel_nand_read_buf ; 
 int /*<<< orphan*/  atmel_nand_read_byte ; 
 int /*<<< orphan*/  atmel_nand_read_word ; 
 int /*<<< orphan*/  atmel_nand_select_chip ; 
 int /*<<< orphan*/  atmel_nand_setup_data_interface ; 
 int /*<<< orphan*/  atmel_nand_write_buf ; 
 int /*<<< orphan*/  atmel_nand_write_byte ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void atmel_nand_init(struct atmel_nand_controller *nc,
			    struct atmel_nand *nand)
{
	struct nand_chip *chip = &nand->base;
	struct mtd_info *mtd = nand_to_mtd(chip);

	mtd->dev.parent = nc->dev;
	nand->base.controller = &nc->base;

	chip->cmd_ctrl = atmel_nand_cmd_ctrl;
	chip->read_byte = atmel_nand_read_byte;
	chip->read_word = atmel_nand_read_word;
	chip->write_byte = atmel_nand_write_byte;
	chip->read_buf = atmel_nand_read_buf;
	chip->write_buf = atmel_nand_write_buf;
	chip->select_chip = atmel_nand_select_chip;

	if (nc->mck && nc->caps->ops->setup_data_interface)
		chip->setup_data_interface = atmel_nand_setup_data_interface;

	/* Some NANDs require a longer delay than the default one (20us). */
	chip->chip_delay = 40;

	/*
	 * Use a bounce buffer when the buffer passed by the MTD user is not
	 * suitable for DMA.
	 */
	if (nc->dmac)
		chip->options |= NAND_USE_BOUNCE_BUFFER;

	/* Default to HW ECC if pmecc is available. */
	if (nc->pmecc)
		chip->ecc.mode = NAND_ECC_HW;
}