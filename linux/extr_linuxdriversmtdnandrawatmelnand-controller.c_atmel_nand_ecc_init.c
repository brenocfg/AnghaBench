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
struct TYPE_2__ {int mode; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  write_page; int /*<<< orphan*/  read_page; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;
struct atmel_nand_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  NAND_ECC_HW 130 
#define  NAND_ECC_NONE 129 
#define  NAND_ECC_SOFT 128 
 int atmel_nand_pmecc_init (struct nand_chip*) ; 
 int /*<<< orphan*/  atmel_nand_pmecc_read_page ; 
 int /*<<< orphan*/  atmel_nand_pmecc_read_page_raw ; 
 int /*<<< orphan*/  atmel_nand_pmecc_write_page ; 
 int /*<<< orphan*/  atmel_nand_pmecc_write_page_raw ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct atmel_nand_controller* to_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_nand_ecc_init(struct nand_chip *chip)
{
	struct atmel_nand_controller *nc;
	int ret;

	nc = to_nand_controller(chip->controller);

	switch (chip->ecc.mode) {
	case NAND_ECC_NONE:
	case NAND_ECC_SOFT:
		/*
		 * Nothing to do, the core will initialize everything for us.
		 */
		break;

	case NAND_ECC_HW:
		ret = atmel_nand_pmecc_init(chip);
		if (ret)
			return ret;

		chip->ecc.read_page = atmel_nand_pmecc_read_page;
		chip->ecc.write_page = atmel_nand_pmecc_write_page;
		chip->ecc.read_page_raw = atmel_nand_pmecc_read_page_raw;
		chip->ecc.write_page_raw = atmel_nand_pmecc_write_page_raw;
		break;

	default:
		/* Other modes are not supported. */
		dev_err(nc->dev, "Unsupported ECC mode: %d\n",
			chip->ecc.mode);
		return -ENOTSUPP;
	}

	return 0;
}