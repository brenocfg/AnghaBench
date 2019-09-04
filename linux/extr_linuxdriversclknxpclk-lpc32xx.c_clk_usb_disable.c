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
struct lpc32xx_usb_clk {int /*<<< orphan*/  ctrl_disable; scalar_t__ ctrl_mask; int /*<<< orphan*/  enable; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_CLKPWR_USB_CTRL ; 
 int /*<<< orphan*/  clk_regmap ; 
 int /*<<< orphan*/  lpc32xx_usb_clk_read (struct lpc32xx_usb_clk*) ; 
 int /*<<< orphan*/  lpc32xx_usb_clk_write (struct lpc32xx_usb_clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct lpc32xx_usb_clk* to_lpc32xx_usb_clk (struct clk_hw*) ; 

__attribute__((used)) static void clk_usb_disable(struct clk_hw *hw)
{
	struct lpc32xx_usb_clk *clk = to_lpc32xx_usb_clk(hw);
	u32 val = lpc32xx_usb_clk_read(clk);

	val &= ~clk->enable;
	lpc32xx_usb_clk_write(clk, val);

	if (clk->ctrl_mask)
		regmap_update_bits(clk_regmap, LPC32XX_CLKPWR_USB_CTRL,
				   clk->ctrl_mask, clk->ctrl_disable);
}