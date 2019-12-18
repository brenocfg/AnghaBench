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
struct hibmc_drm_private {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ HIBMC_CURRENT_GATE ; 
 unsigned int HIBMC_CURR_GATE_DISPLAY (int) ; 
 unsigned int HIBMC_CURR_GATE_DISPLAY_MASK ; 
 unsigned int HIBMC_CURR_GATE_LOCALMEM (int) ; 
 unsigned int HIBMC_CURR_GATE_LOCALMEM_MASK ; 
 scalar_t__ HIBMC_MISC_CTRL ; 
 unsigned int HIBMC_MSCCTL_LOCALMEM_RESET (int) ; 
 unsigned int HIBMC_MSCCTL_LOCALMEM_RESET_MASK ; 
 int /*<<< orphan*/  HIBMC_PW_MODE_CTL_MODE_MODE0 ; 
 int /*<<< orphan*/  hibmc_set_current_gate (struct hibmc_drm_private*,unsigned int) ; 
 int /*<<< orphan*/  hibmc_set_power_mode (struct hibmc_drm_private*,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void hibmc_hw_config(struct hibmc_drm_private *priv)
{
	unsigned int reg;

	/* On hardware reset, power mode 0 is default. */
	hibmc_set_power_mode(priv, HIBMC_PW_MODE_CTL_MODE_MODE0);

	/* Enable display power gate & LOCALMEM power gate*/
	reg = readl(priv->mmio + HIBMC_CURRENT_GATE);
	reg &= ~HIBMC_CURR_GATE_DISPLAY_MASK;
	reg &= ~HIBMC_CURR_GATE_LOCALMEM_MASK;
	reg |= HIBMC_CURR_GATE_DISPLAY(1);
	reg |= HIBMC_CURR_GATE_LOCALMEM(1);

	hibmc_set_current_gate(priv, reg);

	/*
	 * Reset the memory controller. If the memory controller
	 * is not reset in chip,the system might hang when sw accesses
	 * the memory.The memory should be resetted after
	 * changing the MXCLK.
	 */
	reg = readl(priv->mmio + HIBMC_MISC_CTRL);
	reg &= ~HIBMC_MSCCTL_LOCALMEM_RESET_MASK;
	reg |= HIBMC_MSCCTL_LOCALMEM_RESET(0);
	writel(reg, priv->mmio + HIBMC_MISC_CTRL);

	reg &= ~HIBMC_MSCCTL_LOCALMEM_RESET_MASK;
	reg |= HIBMC_MSCCTL_LOCALMEM_RESET(1);

	writel(reg, priv->mmio + HIBMC_MISC_CTRL);
}