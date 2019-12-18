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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct hlwd_gpio {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ HW_GPIOB_INTFLAG ; 
 struct hlwd_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void hlwd_gpio_irq_ack(struct irq_data *data)
{
	struct hlwd_gpio *hlwd =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	iowrite32be(BIT(data->hwirq), hlwd->regs + HW_GPIOB_INTFLAG);
}