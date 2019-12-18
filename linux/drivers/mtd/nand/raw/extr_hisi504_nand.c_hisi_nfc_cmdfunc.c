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
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;
struct hinfc_host {unsigned int command; int offset; int /*<<< orphan*/ * cache_addr_value; int /*<<< orphan*/  dev; int /*<<< orphan*/  chipselect; int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINFC504_CON ; 
 unsigned int HINFC504_CON_ECCTYPE_MASK ; 
 unsigned int HINFC504_CON_ECCTYPE_SHIFT ; 
#define  NAND_CMD_ERASE1 136 
#define  NAND_CMD_ERASE2 135 
#define  NAND_CMD_PAGEPROG 134 
#define  NAND_CMD_READ0 133 
#define  NAND_CMD_READID 132 
#define  NAND_CMD_READOOB 131 
#define  NAND_CMD_RESET 130 
#define  NAND_CMD_SEQIN 129 
#define  NAND_CMD_STATUS 128 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int,int) ; 
 unsigned int hinfc_read (struct hinfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinfc_write (struct hinfc_host*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_nfc_send_cmd_erase (struct hinfc_host*) ; 
 int /*<<< orphan*/  hisi_nfc_send_cmd_pageprog (struct hinfc_host*) ; 
 int /*<<< orphan*/  hisi_nfc_send_cmd_readid (struct hinfc_host*) ; 
 int /*<<< orphan*/  hisi_nfc_send_cmd_readstart (struct hinfc_host*) ; 
 int /*<<< orphan*/  hisi_nfc_send_cmd_reset (struct hinfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_nfc_send_cmd_status (struct hinfc_host*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hinfc_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  set_addr (struct mtd_info*,int,int) ; 

__attribute__((used)) static void hisi_nfc_cmdfunc(struct nand_chip *chip, unsigned command,
			     int column, int page_addr)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct hinfc_host *host = nand_get_controller_data(chip);
	int is_cache_invalid = 1;
	unsigned int flag = 0;

	host->command =  command;

	switch (command) {
	case NAND_CMD_READ0:
	case NAND_CMD_READOOB:
		if (command == NAND_CMD_READ0)
			host->offset = column;
		else
			host->offset = column + mtd->writesize;

		is_cache_invalid = 0;
		set_addr(mtd, column, page_addr);
		hisi_nfc_send_cmd_readstart(host);
		break;

	case NAND_CMD_SEQIN:
		host->offset = column;
		set_addr(mtd, column, page_addr);
		break;

	case NAND_CMD_ERASE1:
		set_addr(mtd, column, page_addr);
		break;

	case NAND_CMD_PAGEPROG:
		hisi_nfc_send_cmd_pageprog(host);
		break;

	case NAND_CMD_ERASE2:
		hisi_nfc_send_cmd_erase(host);
		break;

	case NAND_CMD_READID:
		host->offset = column;
		memset(host->mmio, 0, 0x10);
		hisi_nfc_send_cmd_readid(host);
		break;

	case NAND_CMD_STATUS:
		flag = hinfc_read(host, HINFC504_CON);
		if (chip->ecc.mode == NAND_ECC_HW)
			hinfc_write(host,
				    flag & ~(HINFC504_CON_ECCTYPE_MASK <<
				    HINFC504_CON_ECCTYPE_SHIFT), HINFC504_CON);

		host->offset = 0;
		memset(host->mmio, 0, 0x10);
		hisi_nfc_send_cmd_status(host);
		hinfc_write(host, flag, HINFC504_CON);
		break;

	case NAND_CMD_RESET:
		hisi_nfc_send_cmd_reset(host, host->chipselect);
		break;

	default:
		dev_err(host->dev, "Error: unsupported cmd(cmd=%x, col=%x, page=%x)\n",
			command, column, page_addr);
	}

	if (is_cache_invalid) {
		host->cache_addr_value[0] = ~0;
		host->cache_addr_value[1] = ~0;
	}
}