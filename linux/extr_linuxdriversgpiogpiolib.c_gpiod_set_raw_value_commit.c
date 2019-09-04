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
struct gpio_desc {TYPE_1__* gdev; } ;
struct gpio_chip {int /*<<< orphan*/  (* set ) (struct gpio_chip*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_2__ {struct gpio_chip* chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  desc_to_gpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpio_chip_hwgpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  stub1 (struct gpio_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_gpio_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gpiod_set_raw_value_commit(struct gpio_desc *desc, bool value)
{
	struct gpio_chip	*chip;

	chip = desc->gdev->chip;
	trace_gpio_value(desc_to_gpio(desc), 0, value);
	chip->set(chip, gpio_chip_hwgpio(desc), value);
}