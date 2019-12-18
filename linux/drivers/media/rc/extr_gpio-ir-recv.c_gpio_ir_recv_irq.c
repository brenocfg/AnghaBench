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
struct gpio_rc_dev {int /*<<< orphan*/  rcdev; int /*<<< orphan*/  gpiod; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_store_edge (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t gpio_ir_recv_irq(int irq, void *dev_id)
{
	int val;
	struct gpio_rc_dev *gpio_dev = dev_id;

	val = gpiod_get_value(gpio_dev->gpiod);
	if (val >= 0)
		ir_raw_event_store_edge(gpio_dev->rcdev, val == 1);

	return IRQ_HANDLED;
}