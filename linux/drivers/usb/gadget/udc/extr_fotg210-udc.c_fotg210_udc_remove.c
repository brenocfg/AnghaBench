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
struct fotg210_udc {struct fotg210_udc** ep; int /*<<< orphan*/  ep0_req; int /*<<< orphan*/  reg; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int FOTG210_MAX_NUM_EP ; 
 int /*<<< orphan*/  fotg210_ep_free_request (struct fotg210_udc***,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fotg210_udc*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fotg210_udc*) ; 
 struct fotg210_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fotg210_udc_remove(struct platform_device *pdev)
{
	struct fotg210_udc *fotg210 = platform_get_drvdata(pdev);
	int i;

	usb_del_gadget_udc(&fotg210->gadget);
	iounmap(fotg210->reg);
	free_irq(platform_get_irq(pdev, 0), fotg210);

	fotg210_ep_free_request(&fotg210->ep[0]->ep, fotg210->ep0_req);
	for (i = 0; i < FOTG210_MAX_NUM_EP; i++)
		kfree(fotg210->ep[i]);
	kfree(fotg210);

	return 0;
}