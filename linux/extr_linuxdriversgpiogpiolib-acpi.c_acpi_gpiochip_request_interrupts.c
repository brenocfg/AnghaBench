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
struct gpio_chip {int /*<<< orphan*/  parent; int /*<<< orphan*/  to_irq; } ;
struct acpi_gpio_chip {int /*<<< orphan*/  deferred_req_irqs_list_entry; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  acpi_gpio_chip_dh ; 
 int /*<<< orphan*/  acpi_gpio_deferred_req_irqs_done ; 
 int /*<<< orphan*/  acpi_gpio_deferred_req_irqs_list ; 
 int /*<<< orphan*/  acpi_gpio_deferred_req_irqs_lock ; 
 int /*<<< orphan*/  acpi_gpiochip_alloc_event ; 
 int /*<<< orphan*/  acpi_gpiochip_request_irqs (struct acpi_gpio_chip*) ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct acpi_gpio_chip*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void acpi_gpiochip_request_interrupts(struct gpio_chip *chip)
{
	struct acpi_gpio_chip *acpi_gpio;
	acpi_handle handle;
	acpi_status status;
	bool defer;

	if (!chip->parent || !chip->to_irq)
		return;

	handle = ACPI_HANDLE(chip->parent);
	if (!handle)
		return;

	status = acpi_get_data(handle, acpi_gpio_chip_dh, (void **)&acpi_gpio);
	if (ACPI_FAILURE(status))
		return;

	acpi_walk_resources(handle, "_AEI",
			    acpi_gpiochip_alloc_event, acpi_gpio);

	mutex_lock(&acpi_gpio_deferred_req_irqs_lock);
	defer = !acpi_gpio_deferred_req_irqs_done;
	if (defer)
		list_add(&acpi_gpio->deferred_req_irqs_list_entry,
			 &acpi_gpio_deferred_req_irqs_list);
	mutex_unlock(&acpi_gpio_deferred_req_irqs_lock);

	if (defer)
		return;

	acpi_gpiochip_request_irqs(acpi_gpio);
}