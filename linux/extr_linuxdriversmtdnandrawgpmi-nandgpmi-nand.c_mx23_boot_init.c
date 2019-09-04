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
typedef  int uint8_t ;
struct nand_chip {unsigned int chipsize; unsigned int phys_erase_shift; unsigned int chip_shift; unsigned int page_shift; int (* read_byte ) (struct mtd_info*) ;int (* block_markbad ) (struct mtd_info*,unsigned int) ;int /*<<< orphan*/  (* select_chip ) (struct mtd_info*,int) ;} ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;
struct gpmi_nand_data {struct nand_chip nand; struct device* dev; } ;
struct device {int dummy; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 scalar_t__ mx23_check_transcription_stamp (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  mx23_write_transcription_stamp (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int) ; 
 int stub2 (struct mtd_info*) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int) ; 
 int stub4 (struct mtd_info*,unsigned int) ; 

__attribute__((used)) static int mx23_boot_init(struct gpmi_nand_data  *this)
{
	struct device *dev = this->dev;
	struct nand_chip *chip = &this->nand;
	struct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int block_count;
	unsigned int block;
	int     chipnr;
	int     page;
	loff_t  byte;
	uint8_t block_mark;
	int     ret = 0;

	/*
	 * If control arrives here, we can't use block mark swapping, which
	 * means we're forced to use transcription. First, scan for the
	 * transcription stamp. If we find it, then we don't have to do
	 * anything -- the block marks are already transcribed.
	 */
	if (mx23_check_transcription_stamp(this))
		return 0;

	/*
	 * If control arrives here, we couldn't find a transcription stamp, so
	 * so we presume the block marks are in the conventional location.
	 */
	dev_dbg(dev, "Transcribing bad block marks...\n");

	/* Compute the number of blocks in the entire medium. */
	block_count = chip->chipsize >> chip->phys_erase_shift;

	/*
	 * Loop over all the blocks in the medium, transcribing block marks as
	 * we go.
	 */
	for (block = 0; block < block_count; block++) {
		/*
		 * Compute the chip, page and byte addresses for this block's
		 * conventional mark.
		 */
		chipnr = block >> (chip->chip_shift - chip->phys_erase_shift);
		page = block << (chip->phys_erase_shift - chip->page_shift);
		byte = block <<  chip->phys_erase_shift;

		/* Send the command to read the conventional block mark. */
		chip->select_chip(mtd, chipnr);
		nand_read_page_op(chip, page, mtd->writesize, NULL, 0);
		block_mark = chip->read_byte(mtd);
		chip->select_chip(mtd, -1);

		/*
		 * Check if the block is marked bad. If so, we need to mark it
		 * again, but this time the result will be a mark in the
		 * location where we transcribe block marks.
		 */
		if (block_mark != 0xff) {
			dev_dbg(dev, "Transcribing mark in block %u\n", block);
			ret = chip->block_markbad(mtd, byte);
			if (ret)
				dev_err(dev,
					"Failed to mark block bad with ret %d\n",
					ret);
		}
	}

	/* Write the stamp that indicates we've transcribed the block marks. */
	mx23_write_transcription_stamp(this);
	return 0;
}