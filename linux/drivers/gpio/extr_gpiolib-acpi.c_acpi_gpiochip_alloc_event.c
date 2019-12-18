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
struct gpio_desc {int dummy; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct acpi_resource_gpio {int* pin_table; scalar_t__ triggering; int polarity; scalar_t__ wake_capable; } ;
struct acpi_resource {int dummy; } ;
struct acpi_gpio_event {int irqflags; int irq; int irq_is_wake; int pin; int /*<<< orphan*/  node; struct gpio_desc* desc; int /*<<< orphan*/ * handler; int /*<<< orphan*/  handle; } ;
struct acpi_gpio_chip {int /*<<< orphan*/  events; struct gpio_chip* chip; } ;
typedef  int /*<<< orphan*/ * irq_handler_t ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
#define  ACPI_ACTIVE_HIGH 129 
#define  ACPI_ACTIVE_LOW 128 
 scalar_t__ ACPI_EDGE_SENSITIVE ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_LEVEL_SENSITIVE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_WAKE_CAPABLE ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIO_ACTIVE_HIGH ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_HIGH ; 
 int IRQF_TRIGGER_LOW ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_gpio_get_irq_resource (struct acpi_resource*,struct acpi_resource_gpio**) ; 
 int /*<<< orphan*/ * acpi_gpio_irq_handler ; 
 int /*<<< orphan*/ * acpi_gpio_irq_handler_evt ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiochip_free_own_desc (struct gpio_desc*) ; 
 int gpiochip_lock_as_irq (struct gpio_chip*,int) ; 
 struct gpio_desc* gpiochip_request_own_desc (struct gpio_chip*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_unlock_as_irq (struct gpio_chip*,int) ; 
 int gpiod_to_irq (struct gpio_desc*) ; 
 struct acpi_gpio_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,int) ; 

__attribute__((used)) static acpi_status acpi_gpiochip_alloc_event(struct acpi_resource *ares,
					     void *context)
{
	struct acpi_gpio_chip *acpi_gpio = context;
	struct gpio_chip *chip = acpi_gpio->chip;
	struct acpi_resource_gpio *agpio;
	acpi_handle handle, evt_handle;
	struct acpi_gpio_event *event;
	irq_handler_t handler = NULL;
	struct gpio_desc *desc;
	int ret, pin, irq;

	if (!acpi_gpio_get_irq_resource(ares, &agpio))
		return AE_OK;

	handle = ACPI_HANDLE(chip->parent);
	pin = agpio->pin_table[0];

	if (pin <= 255) {
		char ev_name[5];
		sprintf(ev_name, "_%c%02hhX",
			agpio->triggering == ACPI_EDGE_SENSITIVE ? 'E' : 'L',
			pin);
		if (ACPI_SUCCESS(acpi_get_handle(handle, ev_name, &evt_handle)))
			handler = acpi_gpio_irq_handler;
	}
	if (!handler) {
		if (ACPI_SUCCESS(acpi_get_handle(handle, "_EVT", &evt_handle)))
			handler = acpi_gpio_irq_handler_evt;
	}
	if (!handler)
		return AE_OK;

	desc = gpiochip_request_own_desc(chip, pin, "ACPI:Event",
					 GPIO_ACTIVE_HIGH, GPIOD_IN);
	if (IS_ERR(desc)) {
		dev_err(chip->parent, "Failed to request GPIO\n");
		return AE_ERROR;
	}

	ret = gpiochip_lock_as_irq(chip, pin);
	if (ret) {
		dev_err(chip->parent, "Failed to lock GPIO as interrupt\n");
		goto fail_free_desc;
	}

	irq = gpiod_to_irq(desc);
	if (irq < 0) {
		dev_err(chip->parent, "Failed to translate GPIO to IRQ\n");
		goto fail_unlock_irq;
	}

	event = kzalloc(sizeof(*event), GFP_KERNEL);
	if (!event)
		goto fail_unlock_irq;

	event->irqflags = IRQF_ONESHOT;
	if (agpio->triggering == ACPI_LEVEL_SENSITIVE) {
		if (agpio->polarity == ACPI_ACTIVE_HIGH)
			event->irqflags |= IRQF_TRIGGER_HIGH;
		else
			event->irqflags |= IRQF_TRIGGER_LOW;
	} else {
		switch (agpio->polarity) {
		case ACPI_ACTIVE_HIGH:
			event->irqflags |= IRQF_TRIGGER_RISING;
			break;
		case ACPI_ACTIVE_LOW:
			event->irqflags |= IRQF_TRIGGER_FALLING;
			break;
		default:
			event->irqflags |= IRQF_TRIGGER_RISING |
					   IRQF_TRIGGER_FALLING;
			break;
		}
	}

	event->handle = evt_handle;
	event->handler = handler;
	event->irq = irq;
	event->irq_is_wake = agpio->wake_capable == ACPI_WAKE_CAPABLE;
	event->pin = pin;
	event->desc = desc;

	list_add_tail(&event->node, &acpi_gpio->events);

	return AE_OK;

fail_unlock_irq:
	gpiochip_unlock_as_irq(chip, pin);
fail_free_desc:
	gpiochip_free_own_desc(desc);

	return AE_ERROR;
}