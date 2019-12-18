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
struct nand_chip {int dummy; } ;
struct meson_nfc_nand_chip {int nsels; scalar_t__ clk_rate; int bus_timing; int /*<<< orphan*/  tbers_max; int /*<<< orphan*/  tadl; int /*<<< orphan*/  twb; scalar_t__* sels; } ;
struct TYPE_4__ {int /*<<< orphan*/  tbers_max; int /*<<< orphan*/  tadl; int /*<<< orphan*/  twb; } ;
struct TYPE_3__ {int /*<<< orphan*/  chip_select; int /*<<< orphan*/  rb_select; } ;
struct meson_nfc {scalar_t__ clk_rate; int bus_timing; scalar_t__ reg_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  device_clk; TYPE_2__ timing; TYPE_1__ param; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CE0 ; 
 int /*<<< orphan*/  NAND_CE1 ; 
 int NFC_CLK_CYCLE ; 
 scalar_t__ NFC_REG_CFG ; 
 scalar_t__ NFC_REG_CMD ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct meson_nfc* nand_get_controller_data (struct nand_chip*) ; 
 struct meson_nfc_nand_chip* to_meson_nand (struct nand_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void meson_nfc_select_chip(struct nand_chip *nand, int chip)
{
	struct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	struct meson_nfc *nfc = nand_get_controller_data(nand);
	int ret, value;

	if (chip < 0 || WARN_ON_ONCE(chip >= meson_chip->nsels))
		return;

	nfc->param.chip_select = meson_chip->sels[chip] ? NAND_CE1 : NAND_CE0;
	nfc->param.rb_select = nfc->param.chip_select;
	nfc->timing.twb = meson_chip->twb;
	nfc->timing.tadl = meson_chip->tadl;
	nfc->timing.tbers_max = meson_chip->tbers_max;

	if (nfc->clk_rate != meson_chip->clk_rate) {
		ret = clk_set_rate(nfc->device_clk, meson_chip->clk_rate);
		if (ret) {
			dev_err(nfc->dev, "failed to set clock rate\n");
			return;
		}
		nfc->clk_rate = meson_chip->clk_rate;
	}
	if (nfc->bus_timing != meson_chip->bus_timing) {
		value = (NFC_CLK_CYCLE - 1) | (meson_chip->bus_timing << 5);
		writel(value, nfc->reg_base + NFC_REG_CFG);
		writel((1 << 31), nfc->reg_base + NFC_REG_CMD);
		nfc->bus_timing =  meson_chip->bus_timing;
	}
}