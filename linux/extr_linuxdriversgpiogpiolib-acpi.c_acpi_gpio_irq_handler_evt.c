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
struct acpi_gpio_event {int /*<<< orphan*/  pin; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t acpi_gpio_irq_handler_evt(int irq, void *data)
{
	struct acpi_gpio_event *event = data;

	acpi_execute_simple_method(event->handle, NULL, event->pin);

	return IRQ_HANDLED;
}