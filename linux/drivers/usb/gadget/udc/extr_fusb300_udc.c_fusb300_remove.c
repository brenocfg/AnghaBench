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
struct platform_device {int dummy; } ;
struct fusb300 {struct fusb300** ep; int /*<<< orphan*/  ep0_req; int /*<<< orphan*/  reg; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int FUSB300_MAX_NUM_EP ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fusb300*) ; 
 int /*<<< orphan*/  fusb300_free_request (struct fusb300***,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fusb300*) ; 
 struct fusb300* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fusb300_remove(struct platform_device *pdev)
{
	struct fusb300 *fusb300 = platform_get_drvdata(pdev);
	int i;

	usb_del_gadget_udc(&fusb300->gadget);
	iounmap(fusb300->reg);
	free_irq(platform_get_irq(pdev, 0), fusb300);

	fusb300_free_request(&fusb300->ep[0]->ep, fusb300->ep0_req);
	for (i = 0; i < FUSB300_MAX_NUM_EP; i++)
		kfree(fusb300->ep[i]);
	kfree(fusb300);

	return 0;
}