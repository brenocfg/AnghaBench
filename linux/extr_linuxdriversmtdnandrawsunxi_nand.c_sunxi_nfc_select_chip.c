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
struct sunxi_nfc {scalar_t__ clk_rate; scalar_t__ regs; int /*<<< orphan*/  mod_clk; } ;
struct sunxi_nand_chip_sel {scalar_t__ rb; int /*<<< orphan*/  cs; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct sunxi_nand_chip {int nsels; int selected; scalar_t__ clk_rate; int timing_ctl; int timing_cfg; struct sunxi_nand_chip_sel* sels; TYPE_1__ nand; } ;
struct nand_chip {int /*<<< orphan*/ * dev_ready; int /*<<< orphan*/  page_shift; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int NFC_CE_SEL (int /*<<< orphan*/ ) ; 
 int NFC_CE_SEL_MSK ; 
 int NFC_EN ; 
 int NFC_PAGE_SHIFT (int /*<<< orphan*/ ) ; 
 int NFC_PAGE_SHIFT_MSK ; 
 int NFC_RB_SEL (scalar_t__) ; 
 int NFC_RB_SEL_MSK ; 
 scalar_t__ NFC_REG_CTL ; 
 scalar_t__ NFC_REG_SPARE_AREA ; 
 scalar_t__ NFC_REG_TIMING_CFG ; 
 scalar_t__ NFC_REG_TIMING_CTL ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/ * sunxi_nfc_dev_ready ; 
 struct sunxi_nand_chip* to_sunxi_nand (struct nand_chip*) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sunxi_nfc_select_chip(struct mtd_info *mtd, int chip)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	struct sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.controller);
	struct sunxi_nand_chip_sel *sel;
	u32 ctl;

	if (chip > 0 && chip >= sunxi_nand->nsels)
		return;

	if (chip == sunxi_nand->selected)
		return;

	ctl = readl(nfc->regs + NFC_REG_CTL) &
	      ~(NFC_PAGE_SHIFT_MSK | NFC_CE_SEL_MSK | NFC_RB_SEL_MSK | NFC_EN);

	if (chip >= 0) {
		sel = &sunxi_nand->sels[chip];

		ctl |= NFC_CE_SEL(sel->cs) | NFC_EN |
		       NFC_PAGE_SHIFT(nand->page_shift);
		if (sel->rb < 0) {
			nand->dev_ready = NULL;
		} else {
			nand->dev_ready = sunxi_nfc_dev_ready;
			ctl |= NFC_RB_SEL(sel->rb);
		}

		writel(mtd->writesize, nfc->regs + NFC_REG_SPARE_AREA);

		if (nfc->clk_rate != sunxi_nand->clk_rate) {
			clk_set_rate(nfc->mod_clk, sunxi_nand->clk_rate);
			nfc->clk_rate = sunxi_nand->clk_rate;
		}
	}

	writel(sunxi_nand->timing_ctl, nfc->regs + NFC_REG_TIMING_CTL);
	writel(sunxi_nand->timing_cfg, nfc->regs + NFC_REG_TIMING_CFG);
	writel(ctl, nfc->regs + NFC_REG_CTL);

	sunxi_nand->selected = chip;
}