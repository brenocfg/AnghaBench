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
struct usb_hcd {int dummy; } ;
struct r8a66597 {int /*<<< orphan*/  clk; TYPE_1__* pdata; int /*<<< orphan*/  reg; int /*<<< orphan*/  rh_timer; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ on_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct r8a66597* platform_get_drvdata (struct platform_device*) ; 
 struct usb_hcd* r8a66597_to_hcd (struct r8a66597*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int r8a66597_remove(struct platform_device *pdev)
{
	struct r8a66597		*r8a66597 = platform_get_drvdata(pdev);
	struct usb_hcd		*hcd = r8a66597_to_hcd(r8a66597);

	del_timer_sync(&r8a66597->rh_timer);
	usb_remove_hcd(hcd);
	iounmap(r8a66597->reg);
	if (r8a66597->pdata->on_chip)
		clk_put(r8a66597->clk);
	usb_put_hcd(hcd);
	return 0;
}