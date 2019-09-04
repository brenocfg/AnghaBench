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
struct gpio {int id; int output_state; int /*<<< orphan*/  mode; int /*<<< orphan*/  en; int /*<<< orphan*/ * pin; struct gpio_service* service; } ;
typedef  enum gpio_pin_output_state { ____Placeholder_gpio_pin_output_state } gpio_pin_output_state ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIO_MODE_UNKNOWN ; 
 struct gpio* kzalloc (int,int /*<<< orphan*/ ) ; 

struct gpio *dal_gpio_create(
	struct gpio_service *service,
	enum gpio_id id,
	uint32_t en,
	enum gpio_pin_output_state output_state)
{
	struct gpio *gpio = kzalloc(sizeof(struct gpio), GFP_KERNEL);

	if (!gpio) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	gpio->service = service;
	gpio->pin = NULL;
	gpio->id = id;
	gpio->en = en;
	gpio->mode = GPIO_MODE_UNKNOWN;
	gpio->output_state = output_state;

	return gpio;
}