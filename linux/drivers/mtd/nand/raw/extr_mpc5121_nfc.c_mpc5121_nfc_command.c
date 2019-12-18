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
struct nand_chip {int options; } ;
struct mtd_info {int writesize; } ;
struct mpc5121_nfc_prv {int column; int spareonly; } ;

/* Variables and functions */
 int NAND_BUSWIDTH_16 ; 
#define  NAND_CMD_ERASE1 136 
#define  NAND_CMD_ERASE2 135 
#define  NAND_CMD_PAGEPROG 134 
#define  NAND_CMD_READ0 133 
#define  NAND_CMD_READ1 132 
#define  NAND_CMD_READID 131 
#define  NAND_CMD_READOOB 130 
 unsigned int NAND_CMD_READSTART ; 
#define  NAND_CMD_SEQIN 129 
#define  NAND_CMD_STATUS 128 
 int /*<<< orphan*/  mpc5121_nfc_addr_cycle (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  mpc5121_nfc_send_cmd (struct mtd_info*,unsigned int) ; 
 int /*<<< orphan*/  mpc5121_nfc_send_prog_page (struct mtd_info*) ; 
 int /*<<< orphan*/  mpc5121_nfc_send_read_id (struct mtd_info*) ; 
 int /*<<< orphan*/  mpc5121_nfc_send_read_page (struct mtd_info*) ; 
 int /*<<< orphan*/  mpc5121_nfc_send_read_status (struct mtd_info*) ; 
 struct mpc5121_nfc_prv* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void mpc5121_nfc_command(struct nand_chip *chip, unsigned command,
				int column, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct mpc5121_nfc_prv *prv = nand_get_controller_data(chip);

	prv->column = (column >= 0) ? column : 0;
	prv->spareonly = 0;

	switch (command) {
	case NAND_CMD_PAGEPROG:
		mpc5121_nfc_send_prog_page(mtd);
		break;
	/*
	 * NFC does not support sub-page reads and writes,
	 * so emulate them using full page transfers.
	 */
	case NAND_CMD_READ0:
		column = 0;
		break;

	case NAND_CMD_READ1:
		prv->column += 256;
		command = NAND_CMD_READ0;
		column = 0;
		break;

	case NAND_CMD_READOOB:
		prv->spareonly = 1;
		command = NAND_CMD_READ0;
		column = 0;
		break;

	case NAND_CMD_SEQIN:
		mpc5121_nfc_command(chip, NAND_CMD_READ0, column, page);
		column = 0;
		break;

	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
	case NAND_CMD_READID:
	case NAND_CMD_STATUS:
		break;

	default:
		return;
	}

	mpc5121_nfc_send_cmd(mtd, command);
	mpc5121_nfc_addr_cycle(mtd, column, page);

	switch (command) {
	case NAND_CMD_READ0:
		if (mtd->writesize > 512)
			mpc5121_nfc_send_cmd(mtd, NAND_CMD_READSTART);
		mpc5121_nfc_send_read_page(mtd);
		break;

	case NAND_CMD_READID:
		mpc5121_nfc_send_read_id(mtd);
		break;

	case NAND_CMD_STATUS:
		mpc5121_nfc_send_read_status(mtd);
		if (chip->options & NAND_BUSWIDTH_16)
			prv->column = 1;
		else
			prv->column = 0;
		break;
	}
}