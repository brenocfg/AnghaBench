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
struct acpi_gpio_event {int irqflags; int irq_requested; int /*<<< orphan*/  irq; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,struct acpi_gpio_event*) ;int /*<<< orphan*/  desc; scalar_t__ irq_is_wake; } ;
struct acpi_gpio_chip {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int gpiod_get_raw_value_cansleep (int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,struct acpi_gpio_event*),int,char*,struct acpi_gpio_event*) ; 
 scalar_t__ run_edge_events_on_boot ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct acpi_gpio_event*) ; 

__attribute__((used)) static void acpi_gpiochip_request_irq(struct acpi_gpio_chip *acpi_gpio,
				      struct acpi_gpio_event *event)
{
	int ret, value;

	ret = request_threaded_irq(event->irq, NULL, event->handler,
				   event->irqflags, "ACPI:Event", event);
	if (ret) {
		dev_err(acpi_gpio->chip->parent,
			"Failed to setup interrupt handler for %d\n",
			event->irq);
		return;
	}

	if (event->irq_is_wake)
		enable_irq_wake(event->irq);

	event->irq_requested = true;

	/* Make sure we trigger the initial state of edge-triggered IRQs */
	if (run_edge_events_on_boot &&
	    (event->irqflags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))) {
		value = gpiod_get_raw_value_cansleep(event->desc);
		if (((event->irqflags & IRQF_TRIGGER_RISING) && value == 1) ||
		    ((event->irqflags & IRQF_TRIGGER_FALLING) && value == 0))
			event->handler(event->irq, event);
	}
}