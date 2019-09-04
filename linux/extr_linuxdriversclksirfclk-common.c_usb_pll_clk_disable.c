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
typedef  int u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int SIRFSOC_USBPHY_PLL_BYPASS ; 
 scalar_t__ SIRFSOC_USBPHY_PLL_CTRL ; 
 int SIRFSOC_USBPHY_PLL_POWERDOWN ; 
 int readl (scalar_t__) ; 
 scalar_t__ sirfsoc_rsc_vbase ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void usb_pll_clk_disable(struct clk_hw *clk)
{
	u32 reg = readl(sirfsoc_rsc_vbase + SIRFSOC_USBPHY_PLL_CTRL);
	reg |= (SIRFSOC_USBPHY_PLL_POWERDOWN | SIRFSOC_USBPHY_PLL_BYPASS);
	writel(reg, sirfsoc_rsc_vbase + SIRFSOC_USBPHY_PLL_CTRL);
}