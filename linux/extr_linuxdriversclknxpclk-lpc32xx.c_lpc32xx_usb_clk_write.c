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
struct lpc32xx_usb_clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ LPC32XX_USB_CLK_CTRL ; 
 scalar_t__ usb_clk_vbase ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void lpc32xx_usb_clk_write(struct lpc32xx_usb_clk *clk, u32 val)
{
	writel(val, usb_clk_vbase + LPC32XX_USB_CLK_CTRL);
}