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

/* Variables and functions */
 int /*<<< orphan*/  DRIVER ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int gpio_direction_input (int) ; 
 int gpio_request (int,char*) ; 
 int gpio_to_irq (int) ; 
 int irq_set_irq_type (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isr ; 
 int /*<<< orphan*/  ixp_clock ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_interrupt(int gpio)
{
	int irq;
	int err;

	err = gpio_request(gpio, "ixp4-ptp");
	if (err)
		return err;

	err = gpio_direction_input(gpio);
	if (err)
		return err;

	irq = gpio_to_irq(gpio);
	if (irq < 0)
		return irq;

	err = irq_set_irq_type(irq, IRQF_TRIGGER_FALLING);
	if (err) {
		pr_err("cannot set trigger type for irq %d\n", irq);
		return err;
	}

	err = request_irq(irq, isr, 0, DRIVER, &ixp_clock);
	if (err) {
		pr_err("request_irq failed for irq %d\n", irq);
		return err;
	}

	return irq;
}