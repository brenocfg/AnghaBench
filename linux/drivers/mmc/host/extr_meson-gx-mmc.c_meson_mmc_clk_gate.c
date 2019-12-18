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
typedef  int /*<<< orphan*/  u32 ;
struct meson_host {scalar_t__ regs; scalar_t__ pins_clk_gate; int /*<<< orphan*/  pinctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_STOP_CLOCK ; 
 scalar_t__ SD_EMMC_CFG ; 
 int /*<<< orphan*/  pinctrl_select_state (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_mmc_clk_gate(struct meson_host *host)
{
	u32 cfg;

	if (host->pins_clk_gate) {
		pinctrl_select_state(host->pinctrl, host->pins_clk_gate);
	} else {
		/*
		 * If the pinmux is not provided - default to the classic and
		 * unsafe method
		 */
		cfg = readl(host->regs + SD_EMMC_CFG);
		cfg |= CFG_STOP_CLOCK;
		writel(cfg, host->regs + SD_EMMC_CFG);
	}
}