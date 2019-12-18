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
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  write_page; int /*<<< orphan*/  read_page; } ;
struct nand_chip {TYPE_1__ ecc; } ;

/* Variables and functions */
 scalar_t__ NAND_ECC_HW ; 
 int /*<<< orphan*/  atmel_hsmc_nand_pmecc_read_page ; 
 int /*<<< orphan*/  atmel_hsmc_nand_pmecc_read_page_raw ; 
 int /*<<< orphan*/  atmel_hsmc_nand_pmecc_write_page ; 
 int /*<<< orphan*/  atmel_hsmc_nand_pmecc_write_page_raw ; 
 int atmel_nand_ecc_init (struct nand_chip*) ; 

__attribute__((used)) static int atmel_hsmc_nand_ecc_init(struct nand_chip *chip)
{
	int ret;

	ret = atmel_nand_ecc_init(chip);
	if (ret)
		return ret;

	if (chip->ecc.mode != NAND_ECC_HW)
		return 0;

	/* Adjust the ECC operations for the HSMC IP. */
	chip->ecc.read_page = atmel_hsmc_nand_pmecc_read_page;
	chip->ecc.write_page = atmel_hsmc_nand_pmecc_write_page;
	chip->ecc.read_page_raw = atmel_hsmc_nand_pmecc_read_page_raw;
	chip->ecc.write_page_raw = atmel_hsmc_nand_pmecc_write_page_raw;

	return 0;
}