#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct m66592 {int /*<<< orphan*/  clk; TYPE_2__* pdata; int /*<<< orphan*/  ep0_req; TYPE_1__* ep; int /*<<< orphan*/  reg; int /*<<< orphan*/  timer; int /*<<< orphan*/  gadget; } ;
struct TYPE_4__ {scalar_t__ on_chip; } ;
struct TYPE_3__ {int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct m66592*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct m66592*) ; 
 int /*<<< orphan*/  m66592_free_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct m66592* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int m66592_remove(struct platform_device *pdev)
{
	struct m66592		*m66592 = platform_get_drvdata(pdev);

	usb_del_gadget_udc(&m66592->gadget);

	del_timer_sync(&m66592->timer);
	iounmap(m66592->reg);
	free_irq(platform_get_irq(pdev, 0), m66592);
	m66592_free_request(&m66592->ep[0].ep, m66592->ep0_req);
	if (m66592->pdata->on_chip) {
		clk_disable(m66592->clk);
		clk_put(m66592->clk);
	}
	kfree(m66592);
	return 0;
}