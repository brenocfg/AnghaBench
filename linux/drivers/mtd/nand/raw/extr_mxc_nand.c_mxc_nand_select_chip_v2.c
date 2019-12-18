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
struct nand_chip {int dummy; } ;
struct mxc_nand_host {int clk_act; int active_cs; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_V1_V2_BUF_ADDR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxc_nand_select_chip_v2(struct nand_chip *nand_chip, int chip)
{
	struct mxc_nand_host *host = nand_get_controller_data(nand_chip);

	if (chip == -1) {
		/* Disable the NFC clock */
		if (host->clk_act) {
			clk_disable_unprepare(host->clk);
			host->clk_act = 0;
		}
		return;
	}

	if (!host->clk_act) {
		/* Enable the NFC clock */
		clk_prepare_enable(host->clk);
		host->clk_act = 1;
	}

	host->active_cs = chip;
	writew(host->active_cs << 4, NFC_V1_V2_BUF_ADDR);
}