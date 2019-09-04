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
struct nuc900_nand {int dummy; } ;
struct nand_chip {int options; int /*<<< orphan*/  (* dev_ready ) (struct mtd_info*) ;int /*<<< orphan*/  chip_delay; } ;
struct mtd_info {scalar_t__ writesize; } ;

/* Variables and functions */
 int ENDADDR ; 
 int NAND_BUSWIDTH_16 ; 
#define  NAND_CMD_CACHEDPROG 137 
#define  NAND_CMD_ERASE1 136 
#define  NAND_CMD_ERASE2 135 
#define  NAND_CMD_PAGEPROG 134 
#define  NAND_CMD_READ0 133 
 unsigned int NAND_CMD_READOOB ; 
 unsigned int NAND_CMD_READSTART ; 
#define  NAND_CMD_RESET 132 
#define  NAND_CMD_RNDIN 131 
#define  NAND_CMD_RNDOUT 130 
 unsigned int NAND_CMD_RNDOUTSTART ; 
#define  NAND_CMD_SEQIN 129 
#define  NAND_CMD_STATUS 128 
 int NAND_ROW_ADDR_3 ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct nuc900_nand* mtd_to_nuc900 (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_opcode_8bits (unsigned int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  nuc900_check_rb (struct nuc900_nand*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_addr_reg (struct nuc900_nand*,int) ; 
 int /*<<< orphan*/  write_cmd_reg (struct nuc900_nand*,int const) ; 

__attribute__((used)) static void nuc900_nand_command_lp(struct mtd_info *mtd, unsigned int command,
				   int column, int page_addr)
{
	register struct nand_chip *chip = mtd_to_nand(mtd);
	struct nuc900_nand *nand = mtd_to_nuc900(mtd);

	if (command == NAND_CMD_READOOB) {
		column += mtd->writesize;
		command = NAND_CMD_READ0;
	}

	write_cmd_reg(nand, command & 0xff);

	if (column != -1 || page_addr != -1) {

		if (column != -1) {
			if (chip->options & NAND_BUSWIDTH_16 &&
					!nand_opcode_8bits(command))
				column >>= 1;
			write_addr_reg(nand, column);
			write_addr_reg(nand, column >> 8 | ENDADDR);
		}
		if (page_addr != -1) {
			write_addr_reg(nand, page_addr);

			if (chip->options & NAND_ROW_ADDR_3) {
				write_addr_reg(nand, page_addr >> 8);
				write_addr_reg(nand, page_addr >> 16 | ENDADDR);
			} else {
				write_addr_reg(nand, page_addr >> 8 | ENDADDR);
			}
		}
	}

	switch (command) {
	case NAND_CMD_CACHEDPROG:
	case NAND_CMD_PAGEPROG:
	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_RNDIN:
	case NAND_CMD_STATUS:
		return;

	case NAND_CMD_RESET:
		if (chip->dev_ready)
			break;
		udelay(chip->chip_delay);

		write_cmd_reg(nand, NAND_CMD_STATUS);
		write_cmd_reg(nand, command);

		while (!nuc900_check_rb(nand))
			;

		return;

	case NAND_CMD_RNDOUT:
		write_cmd_reg(nand, NAND_CMD_RNDOUTSTART);
		return;

	case NAND_CMD_READ0:

		write_cmd_reg(nand, NAND_CMD_READSTART);
	default:

		if (!chip->dev_ready) {
			udelay(chip->chip_delay);
			return;
		}
	}

	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
	ndelay(100);

	while (!chip->dev_ready(mtd))
		;
}