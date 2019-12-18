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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ax_device {TYPE_2__* plat; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* check_irq ) (struct platform_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ax_ei_interrupt (int,void*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ax_ei_interrupt_filtered(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct ax_device *ax = to_ax_dev(dev);
	struct platform_device *pdev = to_platform_device(dev->dev.parent);

	if (!ax->plat->check_irq(pdev))
		return IRQ_NONE;

	return ax_ei_interrupt(irq, dev_id);
}