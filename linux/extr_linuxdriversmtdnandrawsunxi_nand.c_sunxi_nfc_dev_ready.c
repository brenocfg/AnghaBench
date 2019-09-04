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
typedef  int u32 ;
struct sunxi_nfc {scalar_t__ regs; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  controller; } ;
struct sunxi_nand_chip {size_t selected; TYPE_1__* sels; TYPE_2__ nand; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ rb; } ;

/* Variables and functions */
 int NFC_RB_STATE (scalar_t__) ; 
 scalar_t__ NFC_REG_ST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int readl (scalar_t__) ; 
 struct sunxi_nand_chip* to_sunxi_nand (struct nand_chip*) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_nfc_dev_ready(struct mtd_info *mtd)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	struct sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.controller);
	u32 mask;

	if (sunxi_nand->selected < 0)
		return 0;

	if (sunxi_nand->sels[sunxi_nand->selected].rb < 0) {
		dev_err(nfc->dev, "cannot check R/B NAND status!\n");
		return 0;
	}

	mask = NFC_RB_STATE(sunxi_nand->sels[sunxi_nand->selected].rb);

	return !!(readl(nfc->regs + NFC_REG_ST) & mask);
}