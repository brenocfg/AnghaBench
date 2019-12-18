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
typedef  int /*<<< orphan*/  uint32_t ;
struct gpio_service {int dummy; } ;
struct gpio {int dummy; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
#define  GPIO_ID_GPIO_PAD 129 
#define  GPIO_ID_HPD 128 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT_STATE_DEFAULT ; 
 struct gpio* dal_gpio_create (struct gpio_service*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct gpio *dal_gpio_create_irq(
	struct gpio_service *service,
	enum gpio_id id,
	uint32_t en)
{
	struct gpio *irq;

	switch (id) {
	case GPIO_ID_HPD:
	case GPIO_ID_GPIO_PAD:
	break;
	default:
		id = GPIO_ID_HPD;
		ASSERT_CRITICAL(false);
		return NULL;
	}

	irq = dal_gpio_create(
		service, id, en, GPIO_PIN_OUTPUT_STATE_DEFAULT);

	if (irq)
		return irq;

	ASSERT_CRITICAL(false);
	return NULL;
}