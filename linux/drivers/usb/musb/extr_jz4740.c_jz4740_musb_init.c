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
struct musb {int dyn_fifo; int /*<<< orphan*/  isr; int /*<<< orphan*/  xceiv; TYPE_1__* controller; } ;
struct device {scalar_t__ of_node; } ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_usb_get_phy (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_usb_get_phy_by_phandle (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_musb_interrupt ; 

__attribute__((used)) static int jz4740_musb_init(struct musb *musb)
{
	struct device *dev = musb->controller->parent;

	if (dev->of_node)
		musb->xceiv = devm_usb_get_phy_by_phandle(dev, "phys", 0);
	else
		musb->xceiv = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
	if (IS_ERR(musb->xceiv)) {
		dev_err(dev, "No transceiver configured\n");
		return PTR_ERR(musb->xceiv);
	}

	/* Silicon does not implement ConfigData register.
	 * Set dyn_fifo to avoid reading EP config from hardware.
	 */
	musb->dyn_fifo = true;

	musb->isr = jz4740_musb_interrupt;

	return 0;
}