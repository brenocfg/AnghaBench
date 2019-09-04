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
struct sunxi_mmc_host {scalar_t__ reg_base; TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  can_calibrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDXC_CAL_DL_SW_EN ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sunxi_mmc_calibrate(struct sunxi_mmc_host *host, int reg_off)
{
	if (!host->cfg->can_calibrate)
		return 0;

	/*
	 * FIXME:
	 * This is not clear how the calibration is supposed to work
	 * yet. The best rate have been obtained by simply setting the
	 * delay to 0, as Allwinner does in its BSP.
	 *
	 * The only mode that doesn't have such a delay is HS400, that
	 * is in itself a TODO.
	 */
	writel(SDXC_CAL_DL_SW_EN, host->reg_base + reg_off);

	return 0;
}