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
struct usba_udc {int clocked; TYPE_1__* pdev; int /*<<< orphan*/  pclk; int /*<<< orphan*/  hclk; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_relax (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_clock(struct usba_udc *udc)
{
	if (!udc->clocked)
		return;

	clk_disable_unprepare(udc->hclk);
	clk_disable_unprepare(udc->pclk);

	udc->clocked = false;

	pm_relax(&udc->pdev->dev);
}