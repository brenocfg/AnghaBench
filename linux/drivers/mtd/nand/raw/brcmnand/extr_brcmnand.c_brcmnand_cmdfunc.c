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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nand_chip {int page_shift; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ sector_size_1k; } ;
struct brcmnand_host {unsigned int last_cmd; int last_addr; TYPE_1__ hwcfg; scalar_t__ last_byte; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int /*<<< orphan*/  soc; scalar_t__ flash_cache; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CMD_BLOCK_ERASE ; 
 int CMD_DEVICE_ID_READ ; 
 int CMD_FLASH_RESET ; 
 int CMD_PARAMETER_CHANGE_COL ; 
 int CMD_PARAMETER_READ ; 
 int CMD_SPARE_AREA_READ ; 
 int CMD_STATUS_READ ; 
 int /*<<< orphan*/  FC_BYTES ; 
 int FC_WORDS ; 
 int /*<<< orphan*/  LL_OP_ADDR ; 
 int /*<<< orphan*/  LL_OP_CMD ; 
#define  NAND_CMD_ERASE1 136 
#define  NAND_CMD_GET_FEATURES 135 
#define  NAND_CMD_PARAM 134 
#define  NAND_CMD_READID 133 
#define  NAND_CMD_READOOB 132 
#define  NAND_CMD_RESET 131 
#define  NAND_CMD_RNDOUT 130 
#define  NAND_CMD_SET_FEATURES 129 
#define  NAND_CMD_STATUS 128 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ brcmnand_get_sector_size_1k (struct brcmnand_host*) ; 
 int /*<<< orphan*/  brcmnand_low_level_op (struct brcmnand_host*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  brcmnand_read_fc (struct brcmnand_controller*,int) ; 
 int /*<<< orphan*/  brcmnand_send_cmd (struct brcmnand_host*,int) ; 
 int /*<<< orphan*/  brcmnand_set_cmd_addr (struct mtd_info*,int) ; 
 int /*<<< orphan*/  brcmnand_set_sector_size_1k (struct brcmnand_host*,scalar_t__) ; 
 int /*<<< orphan*/  brcmnand_soc_data_bus_prepare (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcmnand_soc_data_bus_unprepare (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcmnand_waitfunc (struct nand_chip*) ; 
 int /*<<< orphan*/  brcmnand_wp (struct mtd_info*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned long long) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void brcmnand_cmdfunc(struct nand_chip *chip, unsigned command,
			     int column, int page_addr)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct brcmnand_host *host = nand_get_controller_data(chip);
	struct brcmnand_controller *ctrl = host->ctrl;
	u64 addr = (u64)page_addr << chip->page_shift;
	int native_cmd = 0;

	if (command == NAND_CMD_READID || command == NAND_CMD_PARAM ||
			command == NAND_CMD_RNDOUT)
		addr = (u64)column;
	/* Avoid propagating a negative, don't-care address */
	else if (page_addr < 0)
		addr = 0;

	dev_dbg(ctrl->dev, "cmd 0x%x addr 0x%llx\n", command,
		(unsigned long long)addr);

	host->last_cmd = command;
	host->last_byte = 0;
	host->last_addr = addr;

	switch (command) {
	case NAND_CMD_RESET:
		native_cmd = CMD_FLASH_RESET;
		break;
	case NAND_CMD_STATUS:
		native_cmd = CMD_STATUS_READ;
		break;
	case NAND_CMD_READID:
		native_cmd = CMD_DEVICE_ID_READ;
		break;
	case NAND_CMD_READOOB:
		native_cmd = CMD_SPARE_AREA_READ;
		break;
	case NAND_CMD_ERASE1:
		native_cmd = CMD_BLOCK_ERASE;
		brcmnand_wp(mtd, 0);
		break;
	case NAND_CMD_PARAM:
		native_cmd = CMD_PARAMETER_READ;
		break;
	case NAND_CMD_SET_FEATURES:
	case NAND_CMD_GET_FEATURES:
		brcmnand_low_level_op(host, LL_OP_CMD, command, false);
		brcmnand_low_level_op(host, LL_OP_ADDR, column, false);
		break;
	case NAND_CMD_RNDOUT:
		native_cmd = CMD_PARAMETER_CHANGE_COL;
		addr &= ~((u64)(FC_BYTES - 1));
		/*
		 * HW quirk: PARAMETER_CHANGE_COL requires SECTOR_SIZE_1K=0
		 * NB: hwcfg.sector_size_1k may not be initialized yet
		 */
		if (brcmnand_get_sector_size_1k(host)) {
			host->hwcfg.sector_size_1k =
				brcmnand_get_sector_size_1k(host);
			brcmnand_set_sector_size_1k(host, 0);
		}
		break;
	}

	if (!native_cmd)
		return;

	brcmnand_set_cmd_addr(mtd, addr);
	brcmnand_send_cmd(host, native_cmd);
	brcmnand_waitfunc(chip);

	if (native_cmd == CMD_PARAMETER_READ ||
			native_cmd == CMD_PARAMETER_CHANGE_COL) {
		/* Copy flash cache word-wise */
		u32 *flash_cache = (u32 *)ctrl->flash_cache;
		int i;

		brcmnand_soc_data_bus_prepare(ctrl->soc, true);

		/*
		 * Must cache the FLASH_CACHE now, since changes in
		 * SECTOR_SIZE_1K may invalidate it
		 */
		for (i = 0; i < FC_WORDS; i++)
			/*
			 * Flash cache is big endian for parameter pages, at
			 * least on STB SoCs
			 */
			flash_cache[i] = be32_to_cpu(brcmnand_read_fc(ctrl, i));

		brcmnand_soc_data_bus_unprepare(ctrl->soc, true);

		/* Cleanup from HW quirk: restore SECTOR_SIZE_1K */
		if (host->hwcfg.sector_size_1k)
			brcmnand_set_sector_size_1k(host,
						    host->hwcfg.sector_size_1k);
	}

	/* Re-enable protection is necessary only after erase */
	if (command == NAND_CMD_ERASE1)
		brcmnand_wp(mtd, 1);
}