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
struct twl6030_usb {int /*<<< orphan*/  set_vbus_work; int /*<<< orphan*/  usb3v3; int /*<<< orphan*/  irq2; int /*<<< orphan*/  irq1; int /*<<< orphan*/  get_status_work; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_INT_MSK_LINE_C ; 
 int /*<<< orphan*/  REG_INT_MSK_STS_C ; 
 int /*<<< orphan*/  TWL6030_USBOTG_INT_MASK ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct twl6030_usb*) ; 
 struct twl6030_usb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6030_interrupt_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_usb_remove(struct platform_device *pdev)
{
	struct twl6030_usb *twl = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&twl->get_status_work);
	twl6030_interrupt_mask(TWL6030_USBOTG_INT_MASK,
		REG_INT_MSK_LINE_C);
	twl6030_interrupt_mask(TWL6030_USBOTG_INT_MASK,
			REG_INT_MSK_STS_C);
	free_irq(twl->irq1, twl);
	free_irq(twl->irq2, twl);
	regulator_put(twl->usb3v3);
	cancel_work_sync(&twl->set_vbus_work);

	return 0;
}