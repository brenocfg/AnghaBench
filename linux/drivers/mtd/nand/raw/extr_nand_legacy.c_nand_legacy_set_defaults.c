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
struct TYPE_2__ {int chip_delay; scalar_t__ read_byte; scalar_t__ write_buf; scalar_t__ write_byte; scalar_t__ read_buf; scalar_t__ select_chip; int /*<<< orphan*/ * waitfunc; scalar_t__ cmdfunc; } ;
struct nand_chip {unsigned int options; TYPE_1__ legacy; } ;

/* Variables and functions */
 unsigned int NAND_BUSWIDTH_16 ; 
 scalar_t__ nand_command ; 
 scalar_t__ nand_has_exec_op (struct nand_chip*) ; 
 scalar_t__ nand_read_buf ; 
 scalar_t__ nand_read_buf16 ; 
 scalar_t__ nand_read_byte ; 
 scalar_t__ nand_read_byte16 ; 
 scalar_t__ nand_select_chip ; 
 int /*<<< orphan*/ * nand_wait ; 
 scalar_t__ nand_write_buf ; 
 scalar_t__ nand_write_buf16 ; 
 scalar_t__ nand_write_byte ; 
 scalar_t__ nand_write_byte16 ; 

void nand_legacy_set_defaults(struct nand_chip *chip)
{
	unsigned int busw = chip->options & NAND_BUSWIDTH_16;

	if (nand_has_exec_op(chip))
		return;

	/* check for proper chip_delay setup, set 20us if not */
	if (!chip->legacy.chip_delay)
		chip->legacy.chip_delay = 20;

	/* check, if a user supplied command function given */
	if (!chip->legacy.cmdfunc)
		chip->legacy.cmdfunc = nand_command;

	/* check, if a user supplied wait function given */
	if (chip->legacy.waitfunc == NULL)
		chip->legacy.waitfunc = nand_wait;

	if (!chip->legacy.select_chip)
		chip->legacy.select_chip = nand_select_chip;

	/* If called twice, pointers that depend on busw may need to be reset */
	if (!chip->legacy.read_byte || chip->legacy.read_byte == nand_read_byte)
		chip->legacy.read_byte = busw ? nand_read_byte16 : nand_read_byte;
	if (!chip->legacy.write_buf || chip->legacy.write_buf == nand_write_buf)
		chip->legacy.write_buf = busw ? nand_write_buf16 : nand_write_buf;
	if (!chip->legacy.write_byte || chip->legacy.write_byte == nand_write_byte)
		chip->legacy.write_byte = busw ? nand_write_byte16 : nand_write_byte;
	if (!chip->legacy.read_buf || chip->legacy.read_buf == nand_read_buf)
		chip->legacy.read_buf = busw ? nand_read_buf16 : nand_read_buf;
}