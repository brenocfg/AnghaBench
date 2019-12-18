#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int options; } ;
struct sh_flctl {int read_bytes; int index; int erase1_page_addr; int seqin_column; int seqin_page_addr; int seqin_read_cmd; TYPE_2__* pdev; int /*<<< orphan*/  hwecc; int /*<<< orphan*/  page_size; TYPE_1__ chip; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLDTCNTR (struct sh_flctl*) ; 
 int NAND_BUSWIDTH_16 ; 
#define  NAND_CMD_ERASE1 138 
#define  NAND_CMD_ERASE2 137 
#define  NAND_CMD_PAGEPROG 136 
#define  NAND_CMD_READ0 135 
#define  NAND_CMD_READ1 134 
#define  NAND_CMD_READID 133 
#define  NAND_CMD_READOOB 132 
 int NAND_CMD_READSTART ; 
#define  NAND_CMD_RESET 131 
#define  NAND_CMD_RNDOUT 130 
 int NAND_CMD_RNDOUTSTART ; 
#define  NAND_CMD_SEQIN 129 
#define  NAND_CMD_STATUS 128 
 int /*<<< orphan*/  empty_fifo (struct sh_flctl*) ; 
 int /*<<< orphan*/  execmd_read_oob (struct mtd_info*,int) ; 
 int /*<<< orphan*/  execmd_read_page_sector (struct mtd_info*,int) ; 
 int /*<<< orphan*/  execmd_write_oob (struct mtd_info*) ; 
 int /*<<< orphan*/  execmd_write_page_sector (struct mtd_info*) ; 
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  read_datareg (struct sh_flctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_fiforeg (struct sh_flctl*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_addr (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  set_cmd_regs (struct mtd_info*,int const,unsigned int) ; 
 int /*<<< orphan*/  start_translation (struct sh_flctl*) ; 
 int /*<<< orphan*/  wait_completion (struct sh_flctl*) ; 
 int /*<<< orphan*/  write_fiforeg (struct sh_flctl*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flctl_cmdfunc(struct nand_chip *chip, unsigned int command,
			int column, int page_addr)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct sh_flctl *flctl = mtd_to_flctl(mtd);
	uint32_t read_cmd = 0;

	pm_runtime_get_sync(&flctl->pdev->dev);

	flctl->read_bytes = 0;
	if (command != NAND_CMD_PAGEPROG)
		flctl->index = 0;

	switch (command) {
	case NAND_CMD_READ1:
	case NAND_CMD_READ0:
		if (flctl->hwecc) {
			/* read page with hwecc */
			execmd_read_page_sector(mtd, page_addr);
			break;
		}
		if (flctl->page_size)
			set_cmd_regs(mtd, command, (NAND_CMD_READSTART << 8)
				| command);
		else
			set_cmd_regs(mtd, command, command);

		set_addr(mtd, 0, page_addr);

		flctl->read_bytes = mtd->writesize + mtd->oobsize;
		if (flctl->chip.options & NAND_BUSWIDTH_16)
			column >>= 1;
		flctl->index += column;
		goto read_normal_exit;

	case NAND_CMD_READOOB:
		if (flctl->hwecc) {
			/* read page with hwecc */
			execmd_read_oob(mtd, page_addr);
			break;
		}

		if (flctl->page_size) {
			set_cmd_regs(mtd, command, (NAND_CMD_READSTART << 8)
				| NAND_CMD_READ0);
			set_addr(mtd, mtd->writesize, page_addr);
		} else {
			set_cmd_regs(mtd, command, command);
			set_addr(mtd, 0, page_addr);
		}
		flctl->read_bytes = mtd->oobsize;
		goto read_normal_exit;

	case NAND_CMD_RNDOUT:
		if (flctl->hwecc)
			break;

		if (flctl->page_size)
			set_cmd_regs(mtd, command, (NAND_CMD_RNDOUTSTART << 8)
				| command);
		else
			set_cmd_regs(mtd, command, command);

		set_addr(mtd, column, 0);

		flctl->read_bytes = mtd->writesize + mtd->oobsize - column;
		goto read_normal_exit;

	case NAND_CMD_READID:
		set_cmd_regs(mtd, command, command);

		/* READID is always performed using an 8-bit bus */
		if (flctl->chip.options & NAND_BUSWIDTH_16)
			column <<= 1;
		set_addr(mtd, column, 0);

		flctl->read_bytes = 8;
		writel(flctl->read_bytes, FLDTCNTR(flctl)); /* set read size */
		empty_fifo(flctl);
		start_translation(flctl);
		read_fiforeg(flctl, flctl->read_bytes, 0);
		wait_completion(flctl);
		break;

	case NAND_CMD_ERASE1:
		flctl->erase1_page_addr = page_addr;
		break;

	case NAND_CMD_ERASE2:
		set_cmd_regs(mtd, NAND_CMD_ERASE1,
			(command << 8) | NAND_CMD_ERASE1);
		set_addr(mtd, -1, flctl->erase1_page_addr);
		start_translation(flctl);
		wait_completion(flctl);
		break;

	case NAND_CMD_SEQIN:
		if (!flctl->page_size) {
			/* output read command */
			if (column >= mtd->writesize) {
				column -= mtd->writesize;
				read_cmd = NAND_CMD_READOOB;
			} else if (column < 256) {
				read_cmd = NAND_CMD_READ0;
			} else {
				column -= 256;
				read_cmd = NAND_CMD_READ1;
			}
		}
		flctl->seqin_column = column;
		flctl->seqin_page_addr = page_addr;
		flctl->seqin_read_cmd = read_cmd;
		break;

	case NAND_CMD_PAGEPROG:
		empty_fifo(flctl);
		if (!flctl->page_size) {
			set_cmd_regs(mtd, NAND_CMD_SEQIN,
					flctl->seqin_read_cmd);
			set_addr(mtd, -1, -1);
			writel(0, FLDTCNTR(flctl));	/* set 0 size */
			start_translation(flctl);
			wait_completion(flctl);
		}
		if (flctl->hwecc) {
			/* write page with hwecc */
			if (flctl->seqin_column == mtd->writesize)
				execmd_write_oob(mtd);
			else if (!flctl->seqin_column)
				execmd_write_page_sector(mtd);
			else
				pr_err("Invalid address !?\n");
			break;
		}
		set_cmd_regs(mtd, command, (command << 8) | NAND_CMD_SEQIN);
		set_addr(mtd, flctl->seqin_column, flctl->seqin_page_addr);
		writel(flctl->index, FLDTCNTR(flctl));	/* set write size */
		start_translation(flctl);
		write_fiforeg(flctl, flctl->index, 0);
		wait_completion(flctl);
		break;

	case NAND_CMD_STATUS:
		set_cmd_regs(mtd, command, command);
		set_addr(mtd, -1, -1);

		flctl->read_bytes = 1;
		writel(flctl->read_bytes, FLDTCNTR(flctl)); /* set read size */
		start_translation(flctl);
		read_datareg(flctl, 0); /* read and end */
		break;

	case NAND_CMD_RESET:
		set_cmd_regs(mtd, command, command);
		set_addr(mtd, -1, -1);

		writel(0, FLDTCNTR(flctl));	/* set 0 size */
		start_translation(flctl);
		wait_completion(flctl);
		break;

	default:
		break;
	}
	goto runtime_exit;

read_normal_exit:
	writel(flctl->read_bytes, FLDTCNTR(flctl));	/* set read size */
	empty_fifo(flctl);
	start_translation(flctl);
	read_fiforeg(flctl, flctl->read_bytes, 0);
	wait_completion(flctl);
runtime_exit:
	pm_runtime_put_sync(&flctl->pdev->dev);
	return;
}