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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct at91_udc {int /*<<< orphan*/  iclk; int /*<<< orphan*/  fclk; int /*<<< orphan*/  lock; scalar_t__ driver; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct at91_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pullup (struct at91_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_debug_file (struct at91_udc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at91udc_remove(struct platform_device *pdev)
{
	struct at91_udc *udc = platform_get_drvdata(pdev);
	unsigned long	flags;

	DBG("remove\n");

	usb_del_gadget_udc(&udc->gadget);
	if (udc->driver)
		return -EBUSY;

	spin_lock_irqsave(&udc->lock, flags);
	pullup(udc, 0);
	spin_unlock_irqrestore(&udc->lock, flags);

	device_init_wakeup(&pdev->dev, 0);
	remove_debug_file(udc);
	clk_unprepare(udc->fclk);
	clk_unprepare(udc->iclk);

	return 0;
}