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
struct sunxi_nfc {int /*<<< orphan*/  ahb_clk; int /*<<< orphan*/  mod_clk; scalar_t__ dmac; int /*<<< orphan*/  reset; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 struct sunxi_nfc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_nand_chips_cleanup (struct sunxi_nfc*) ; 

__attribute__((used)) static int sunxi_nfc_remove(struct platform_device *pdev)
{
	struct sunxi_nfc *nfc = platform_get_drvdata(pdev);

	sunxi_nand_chips_cleanup(nfc);

	reset_control_assert(nfc->reset);

	if (nfc->dmac)
		dma_release_channel(nfc->dmac);
	clk_disable_unprepare(nfc->mod_clk);
	clk_disable_unprepare(nfc->ahb_clk);

	return 0;
}