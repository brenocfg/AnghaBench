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
struct nand_chip {unsigned int options; int chip_delay; scalar_t__ read_byte; scalar_t__ write_buf; scalar_t__ write_byte; scalar_t__ read_buf; int buf_align; int /*<<< orphan*/ * controller; int /*<<< orphan*/  dummy_controller; scalar_t__ block_markbad; scalar_t__ block_bad; scalar_t__ read_word; scalar_t__ get_features; scalar_t__ set_features; scalar_t__ select_chip; int /*<<< orphan*/ * waitfunc; scalar_t__ cmdfunc; int /*<<< orphan*/  exec_op; } ;

/* Variables and functions */
 unsigned int NAND_BUSWIDTH_16 ; 
 scalar_t__ nand_block_bad ; 
 scalar_t__ nand_command ; 
 int /*<<< orphan*/  nand_controller_init (int /*<<< orphan*/ *) ; 
 scalar_t__ nand_default_block_markbad ; 
 scalar_t__ nand_default_get_features ; 
 scalar_t__ nand_default_set_features ; 
 scalar_t__ nand_read_buf ; 
 scalar_t__ nand_read_buf16 ; 
 scalar_t__ nand_read_byte ; 
 scalar_t__ nand_read_byte16 ; 
 scalar_t__ nand_read_word ; 
 scalar_t__ nand_select_chip ; 
 int /*<<< orphan*/ * nand_wait ; 
 scalar_t__ nand_write_buf ; 
 scalar_t__ nand_write_buf16 ; 
 scalar_t__ nand_write_byte ; 
 scalar_t__ nand_write_byte16 ; 

__attribute__((used)) static void nand_set_defaults(struct nand_chip *chip)
{
	unsigned int busw = chip->options & NAND_BUSWIDTH_16;

	/* check for proper chip_delay setup, set 20us if not */
	if (!chip->chip_delay)
		chip->chip_delay = 20;

	/* check, if a user supplied command function given */
	if (!chip->cmdfunc && !chip->exec_op)
		chip->cmdfunc = nand_command;

	/* check, if a user supplied wait function given */
	if (chip->waitfunc == NULL)
		chip->waitfunc = nand_wait;

	if (!chip->select_chip)
		chip->select_chip = nand_select_chip;

	/* set for ONFI nand */
	if (!chip->set_features)
		chip->set_features = nand_default_set_features;
	if (!chip->get_features)
		chip->get_features = nand_default_get_features;

	/* If called twice, pointers that depend on busw may need to be reset */
	if (!chip->read_byte || chip->read_byte == nand_read_byte)
		chip->read_byte = busw ? nand_read_byte16 : nand_read_byte;
	if (!chip->read_word)
		chip->read_word = nand_read_word;
	if (!chip->block_bad)
		chip->block_bad = nand_block_bad;
	if (!chip->block_markbad)
		chip->block_markbad = nand_default_block_markbad;
	if (!chip->write_buf || chip->write_buf == nand_write_buf)
		chip->write_buf = busw ? nand_write_buf16 : nand_write_buf;
	if (!chip->write_byte || chip->write_byte == nand_write_byte)
		chip->write_byte = busw ? nand_write_byte16 : nand_write_byte;
	if (!chip->read_buf || chip->read_buf == nand_read_buf)
		chip->read_buf = busw ? nand_read_buf16 : nand_read_buf;

	if (!chip->controller) {
		chip->controller = &chip->dummy_controller;
		nand_controller_init(chip->controller);
	}

	if (!chip->buf_align)
		chip->buf_align = 1;
}