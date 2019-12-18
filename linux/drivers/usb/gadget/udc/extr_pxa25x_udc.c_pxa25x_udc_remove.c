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
struct pxa25x_udc {int /*<<< orphan*/ * transceiver; scalar_t__ pullup; int /*<<< orphan*/  gadget; scalar_t__ driver; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 struct pxa25x_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pullup (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  remove_debug_files (struct pxa25x_udc*) ; 
 int /*<<< orphan*/ * the_controller ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa25x_udc_remove(struct platform_device *pdev)
{
	struct pxa25x_udc *dev = platform_get_drvdata(pdev);

	if (dev->driver)
		return -EBUSY;

	usb_del_gadget_udc(&dev->gadget);
	dev->pullup = 0;
	pullup(dev);

	remove_debug_files(dev);

	if (!IS_ERR_OR_NULL(dev->transceiver))
		dev->transceiver = NULL;

	the_controller = NULL;
	return 0;
}