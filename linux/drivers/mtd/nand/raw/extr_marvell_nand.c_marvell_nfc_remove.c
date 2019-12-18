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
struct platform_device {int dummy; } ;
struct marvell_nfc {int /*<<< orphan*/  core_clk; int /*<<< orphan*/  reg_clk; int /*<<< orphan*/  dma_chan; scalar_t__ use_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvell_nand_chips_cleanup (struct marvell_nfc*) ; 
 struct marvell_nfc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int marvell_nfc_remove(struct platform_device *pdev)
{
	struct marvell_nfc *nfc = platform_get_drvdata(pdev);

	marvell_nand_chips_cleanup(nfc);

	if (nfc->use_dma) {
		dmaengine_terminate_all(nfc->dma_chan);
		dma_release_channel(nfc->dma_chan);
	}

	clk_disable_unprepare(nfc->reg_clk);
	clk_disable_unprepare(nfc->core_clk);

	return 0;
}