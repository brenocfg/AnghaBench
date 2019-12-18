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
struct cdns3 {TYPE_1__* otg_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ivect; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DR_MODE_OTG ; 
 int /*<<< orphan*/  cdns3_otg_disable_irq (struct cdns3*) ; 
 int /*<<< orphan*/  cdns3_otg_enable_irq (struct cdns3*) ; 
 int cdns3_set_mode (struct cdns3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns3_init_otg_mode(struct cdns3 *cdns)
{
	int ret = 0;

	cdns3_otg_disable_irq(cdns);
	/* clear all interrupts */
	writel(~0, &cdns->otg_regs->ivect);

	ret = cdns3_set_mode(cdns, USB_DR_MODE_OTG);
	if (ret)
		return ret;

	cdns3_otg_enable_irq(cdns);
	return ret;
}