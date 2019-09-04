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
struct nand_ecc_ctrl {int strength; int /*<<< orphan*/  write_oob; int /*<<< orphan*/  read_oob; int /*<<< orphan*/  write_page; int /*<<< orphan*/  read_page; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  bytes; int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int FIELD_ORDER ; 
 int /*<<< orphan*/  NAND_ECC_BCH ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int /*<<< orphan*/  tango_read_oob ; 
 int /*<<< orphan*/  tango_read_page ; 
 int /*<<< orphan*/  tango_read_page_raw ; 
 int /*<<< orphan*/  tango_write_oob ; 
 int /*<<< orphan*/  tango_write_page ; 
 int /*<<< orphan*/  tango_write_page_raw ; 

__attribute__((used)) static int tango_attach_chip(struct nand_chip *chip)
{
	struct nand_ecc_ctrl *ecc = &chip->ecc;

	ecc->mode = NAND_ECC_HW;
	ecc->algo = NAND_ECC_BCH;
	ecc->bytes = DIV_ROUND_UP(ecc->strength * FIELD_ORDER, BITS_PER_BYTE);

	ecc->read_page_raw = tango_read_page_raw;
	ecc->write_page_raw = tango_write_page_raw;
	ecc->read_page = tango_read_page;
	ecc->write_page = tango_write_page;
	ecc->read_oob = tango_read_oob;
	ecc->write_oob = tango_write_oob;

	return 0;
}