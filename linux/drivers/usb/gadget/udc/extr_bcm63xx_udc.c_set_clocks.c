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
struct bcm63xx_udc {int /*<<< orphan*/  usbh_clk; int /*<<< orphan*/  usbd_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void set_clocks(struct bcm63xx_udc *udc, bool is_enabled)
{
	if (is_enabled) {
		clk_enable(udc->usbh_clk);
		clk_enable(udc->usbd_clk);
		udelay(10);
	} else {
		clk_disable(udc->usbd_clk);
		clk_disable(udc->usbh_clk);
	}
}