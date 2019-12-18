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
struct nand_chip {int dummy; } ;
struct brcmnand_host {int last_cmd; int last_byte; int last_addr; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int* flash_cache; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_ID ; 
 int /*<<< orphan*/  BRCMNAND_ID_EXT ; 
 int /*<<< orphan*/  BRCMNAND_INTFC_STATUS ; 
 int /*<<< orphan*/  BRCMNAND_LL_RDATA ; 
 int /*<<< orphan*/  FC_BYTES ; 
 int INTFC_FLASH_STATUS ; 
 int /*<<< orphan*/  LL_OP_RD ; 
#define  NAND_CMD_GET_FEATURES 133 
#define  NAND_CMD_PARAM 132 
#define  NAND_CMD_READID 131 
#define  NAND_CMD_READOOB 130 
#define  NAND_CMD_RNDOUT 129 
#define  NAND_CMD_STATUS 128 
 int NAND_STATUS_WP ; 
 scalar_t__ ONFI_SUBFEATURE_PARAM_LEN ; 
 int /*<<< orphan*/  brcmnand_low_level_op (struct brcmnand_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int brcmnand_read_reg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nand_change_read_column_op (struct nand_chip*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 
 int oob_reg_read (struct brcmnand_controller*,int) ; 
 int /*<<< orphan*/  wp_on ; 

__attribute__((used)) static uint8_t brcmnand_read_byte(struct nand_chip *chip)
{
	struct brcmnand_host *host = nand_get_controller_data(chip);
	struct brcmnand_controller *ctrl = host->ctrl;
	uint8_t ret = 0;
	int addr, offs;

	switch (host->last_cmd) {
	case NAND_CMD_READID:
		if (host->last_byte < 4)
			ret = brcmnand_read_reg(ctrl, BRCMNAND_ID) >>
				(24 - (host->last_byte << 3));
		else if (host->last_byte < 8)
			ret = brcmnand_read_reg(ctrl, BRCMNAND_ID_EXT) >>
				(56 - (host->last_byte << 3));
		break;

	case NAND_CMD_READOOB:
		ret = oob_reg_read(ctrl, host->last_byte);
		break;

	case NAND_CMD_STATUS:
		ret = brcmnand_read_reg(ctrl, BRCMNAND_INTFC_STATUS) &
					INTFC_FLASH_STATUS;
		if (wp_on) /* hide WP status */
			ret |= NAND_STATUS_WP;
		break;

	case NAND_CMD_PARAM:
	case NAND_CMD_RNDOUT:
		addr = host->last_addr + host->last_byte;
		offs = addr & (FC_BYTES - 1);

		/* At FC_BYTES boundary, switch to next column */
		if (host->last_byte > 0 && offs == 0)
			nand_change_read_column_op(chip, addr, NULL, 0, false);

		ret = ctrl->flash_cache[offs];
		break;
	case NAND_CMD_GET_FEATURES:
		if (host->last_byte >= ONFI_SUBFEATURE_PARAM_LEN) {
			ret = 0;
		} else {
			bool last = host->last_byte ==
				ONFI_SUBFEATURE_PARAM_LEN - 1;
			brcmnand_low_level_op(host, LL_OP_RD, 0, last);
			ret = brcmnand_read_reg(ctrl, BRCMNAND_LL_RDATA) & 0xff;
		}
	}

	dev_dbg(ctrl->dev, "read byte = 0x%02x\n", ret);
	host->last_byte++;

	return ret;
}