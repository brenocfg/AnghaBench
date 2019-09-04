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
typedef  int u32 ;
struct sunxi_nfc {scalar_t__ regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct sunxi_nand_chip {int addr_cycles; int* cmd; int* addr; scalar_t__ cmd_cycles; TYPE_1__ nand; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_NCE ; 
 int NFC_ADR_NUM (int) ; 
 int /*<<< orphan*/  NFC_CMD_INT_FLAG ; 
 scalar_t__ NFC_REG_ADDR_HIGH ; 
 scalar_t__ NFC_REG_ADDR_LOW ; 
 scalar_t__ NFC_REG_CMD ; 
 scalar_t__ NFC_REG_RCMD_SET ; 
 int NFC_SEND_ADR ; 
 int NFC_SEND_CMD1 ; 
 int NFC_SEND_CMD2 ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int sunxi_nfc_wait_cmd_fifo_empty (struct sunxi_nfc*) ; 
 int /*<<< orphan*/  sunxi_nfc_wait_events (struct sunxi_nfc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sunxi_nand_chip* to_sunxi_nand (struct nand_chip*) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sunxi_nfc_cmd_ctrl(struct mtd_info *mtd, int dat,
			       unsigned int ctrl)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	struct sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.controller);
	int ret;

	if (dat == NAND_CMD_NONE && (ctrl & NAND_NCE) &&
	    !(ctrl & (NAND_CLE | NAND_ALE))) {
		u32 cmd = 0;

		if (!sunxi_nand->addr_cycles && !sunxi_nand->cmd_cycles)
			return;

		if (sunxi_nand->cmd_cycles--)
			cmd |= NFC_SEND_CMD1 | sunxi_nand->cmd[0];

		if (sunxi_nand->cmd_cycles--) {
			cmd |= NFC_SEND_CMD2;
			writel(sunxi_nand->cmd[1],
			       nfc->regs + NFC_REG_RCMD_SET);
		}

		sunxi_nand->cmd_cycles = 0;

		if (sunxi_nand->addr_cycles) {
			cmd |= NFC_SEND_ADR |
			       NFC_ADR_NUM(sunxi_nand->addr_cycles);
			writel(sunxi_nand->addr[0],
			       nfc->regs + NFC_REG_ADDR_LOW);
		}

		if (sunxi_nand->addr_cycles > 4)
			writel(sunxi_nand->addr[1],
			       nfc->regs + NFC_REG_ADDR_HIGH);

		ret = sunxi_nfc_wait_cmd_fifo_empty(nfc);
		if (ret)
			return;

		writel(cmd, nfc->regs + NFC_REG_CMD);
		sunxi_nand->addr[0] = 0;
		sunxi_nand->addr[1] = 0;
		sunxi_nand->addr_cycles = 0;
		sunxi_nfc_wait_events(nfc, NFC_CMD_INT_FLAG, true, 0);
	}

	if (ctrl & NAND_CLE) {
		sunxi_nand->cmd[sunxi_nand->cmd_cycles++] = dat;
	} else if (ctrl & NAND_ALE) {
		sunxi_nand->addr[sunxi_nand->addr_cycles / 4] |=
				dat << ((sunxi_nand->addr_cycles % 4) * 8);
		sunxi_nand->addr_cycles++;
	}
}