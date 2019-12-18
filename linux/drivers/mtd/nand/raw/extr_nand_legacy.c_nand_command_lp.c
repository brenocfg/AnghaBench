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
struct TYPE_2__ {int /*<<< orphan*/  chip_delay; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  (* cmd_ctrl ) (struct nand_chip*,unsigned int const,int) ;} ;
struct nand_chip {int options; TYPE_1__ legacy; } ;
struct mtd_info {scalar_t__ writesize; } ;

/* Variables and functions */
 int NAND_ALE ; 
 int NAND_BUSWIDTH_16 ; 
 int NAND_CLE ; 
#define  NAND_CMD_CACHEDPROG 140 
#define  NAND_CMD_ERASE1 139 
#define  NAND_CMD_ERASE2 138 
#define  NAND_CMD_NONE 137 
#define  NAND_CMD_PAGEPROG 136 
#define  NAND_CMD_READ0 135 
#define  NAND_CMD_READID 134 
 unsigned int NAND_CMD_READOOB ; 
 unsigned int const NAND_CMD_READSTART ; 
#define  NAND_CMD_RESET 133 
#define  NAND_CMD_RNDIN 132 
#define  NAND_CMD_RNDOUT 131 
 unsigned int const NAND_CMD_RNDOUTSTART ; 
#define  NAND_CMD_SEQIN 130 
#define  NAND_CMD_SET_FEATURES 129 
#define  NAND_CMD_STATUS 128 
 int NAND_CTRL_CHANGE ; 
 int NAND_NCE ; 
 int NAND_ROW_ADDR_3 ; 
 int /*<<< orphan*/  nand_ccs_delay (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_opcode_8bits (unsigned int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_wait_ready (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_wait_status_ready (struct nand_chip*,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  stub10 (struct nand_chip*,unsigned int const,int) ; 
 int /*<<< orphan*/  stub11 (struct nand_chip*,unsigned int const,int) ; 
 int /*<<< orphan*/  stub12 (struct nand_chip*,unsigned int const,int) ; 
 int /*<<< orphan*/  stub13 (struct nand_chip*,unsigned int const,int) ; 
 int /*<<< orphan*/  stub2 (struct nand_chip*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct nand_chip*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct nand_chip*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct nand_chip*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct nand_chip*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct nand_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  stub8 (struct nand_chip*,int const,int) ; 
 int /*<<< orphan*/  stub9 (struct nand_chip*,unsigned int const,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nand_command_lp(struct nand_chip *chip, unsigned int command,
			    int column, int page_addr)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	/* Emulate NAND_CMD_READOOB */
	if (command == NAND_CMD_READOOB) {
		column += mtd->writesize;
		command = NAND_CMD_READ0;
	}

	/* Command latch cycle */
	if (command != NAND_CMD_NONE)
		chip->legacy.cmd_ctrl(chip, command,
				      NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);

	if (column != -1 || page_addr != -1) {
		int ctrl = NAND_CTRL_CHANGE | NAND_NCE | NAND_ALE;

		/* Serially input address */
		if (column != -1) {
			/* Adjust columns for 16 bit buswidth */
			if (chip->options & NAND_BUSWIDTH_16 &&
					!nand_opcode_8bits(command))
				column >>= 1;
			chip->legacy.cmd_ctrl(chip, column, ctrl);
			ctrl &= ~NAND_CTRL_CHANGE;

			/* Only output a single addr cycle for 8bits opcodes. */
			if (!nand_opcode_8bits(command))
				chip->legacy.cmd_ctrl(chip, column >> 8, ctrl);
		}
		if (page_addr != -1) {
			chip->legacy.cmd_ctrl(chip, page_addr, ctrl);
			chip->legacy.cmd_ctrl(chip, page_addr >> 8,
					     NAND_NCE | NAND_ALE);
			if (chip->options & NAND_ROW_ADDR_3)
				chip->legacy.cmd_ctrl(chip, page_addr >> 16,
						      NAND_NCE | NAND_ALE);
		}
	}
	chip->legacy.cmd_ctrl(chip, NAND_CMD_NONE,
			      NAND_NCE | NAND_CTRL_CHANGE);

	/*
	 * Program and erase have their own busy handlers status, sequential
	 * in and status need no delay.
	 */
	switch (command) {

	case NAND_CMD_NONE:
	case NAND_CMD_CACHEDPROG:
	case NAND_CMD_PAGEPROG:
	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_STATUS:
	case NAND_CMD_READID:
	case NAND_CMD_SET_FEATURES:
		return;

	case NAND_CMD_RNDIN:
		nand_ccs_delay(chip);
		return;

	case NAND_CMD_RESET:
		if (chip->legacy.dev_ready)
			break;
		udelay(chip->legacy.chip_delay);
		chip->legacy.cmd_ctrl(chip, NAND_CMD_STATUS,
				      NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->legacy.cmd_ctrl(chip, NAND_CMD_NONE,
				      NAND_NCE | NAND_CTRL_CHANGE);
		/* EZ-NAND can take upto 250ms as per ONFi v4.0 */
		nand_wait_status_ready(chip, 250);
		return;

	case NAND_CMD_RNDOUT:
		/* No ready / busy check necessary */
		chip->legacy.cmd_ctrl(chip, NAND_CMD_RNDOUTSTART,
				      NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->legacy.cmd_ctrl(chip, NAND_CMD_NONE,
				      NAND_NCE | NAND_CTRL_CHANGE);

		nand_ccs_delay(chip);
		return;

	case NAND_CMD_READ0:
		/*
		 * READ0 is sometimes used to exit GET STATUS mode. When this
		 * is the case no address cycles are requested, and we can use
		 * this information to detect that READSTART should not be
		 * issued.
		 */
		if (column == -1 && page_addr == -1)
			return;

		chip->legacy.cmd_ctrl(chip, NAND_CMD_READSTART,
				      NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->legacy.cmd_ctrl(chip, NAND_CMD_NONE,
				      NAND_NCE | NAND_CTRL_CHANGE);

		/* fall through - This applies to read commands */
	default:
		/*
		 * If we don't have access to the busy pin, we apply the given
		 * command delay.
		 */
		if (!chip->legacy.dev_ready) {
			udelay(chip->legacy.chip_delay);
			return;
		}
	}

	/*
	 * Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine.
	 */
	ndelay(100);

	nand_wait_ready(chip);
}