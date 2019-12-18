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
struct ns2_phy_driver {int /*<<< orphan*/  debounce_jiffies; int /*<<< orphan*/  wq_extcon; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static irqreturn_t gpio_irq_handler(int irq, void *dev_id)
{
	struct ns2_phy_driver *driver = dev_id;

	queue_delayed_work(system_power_efficient_wq, &driver->wq_extcon,
			   driver->debounce_jiffies);

	return IRQ_HANDLED;
}