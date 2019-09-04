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
struct gpio_desc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  FLAG_ACTIVE_LOW ; 
 int /*<<< orphan*/  FLAG_OPEN_DRAIN ; 
 int /*<<< orphan*/  FLAG_OPEN_SOURCE ; 
 unsigned long GPIOF_ACTIVE_LOW ; 
 unsigned long GPIOF_DIR_IN ; 
 unsigned long GPIOF_EXPORT ; 
 unsigned long GPIOF_EXPORT_CHANGEABLE ; 
 unsigned long GPIOF_INIT_HIGH ; 
 unsigned long GPIOF_OPEN_DRAIN ; 
 unsigned long GPIOF_OPEN_SOURCE ; 
 scalar_t__ gpio_is_valid (unsigned int) ; 
 struct gpio_desc* gpio_to_desc (unsigned int) ; 
 int gpiod_direction_input (struct gpio_desc*) ; 
 int gpiod_direction_output_raw (struct gpio_desc*,int) ; 
 int gpiod_export (struct gpio_desc*,unsigned long) ; 
 int /*<<< orphan*/  gpiod_free (struct gpio_desc*) ; 
 int gpiod_request (struct gpio_desc*,char const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int gpio_request_one(unsigned gpio, unsigned long flags, const char *label)
{
	struct gpio_desc *desc;
	int err;

	desc = gpio_to_desc(gpio);

	/* Compatibility: assume unavailable "valid" GPIOs will appear later */
	if (!desc && gpio_is_valid(gpio))
		return -EPROBE_DEFER;

	err = gpiod_request(desc, label);
	if (err)
		return err;

	if (flags & GPIOF_OPEN_DRAIN)
		set_bit(FLAG_OPEN_DRAIN, &desc->flags);

	if (flags & GPIOF_OPEN_SOURCE)
		set_bit(FLAG_OPEN_SOURCE, &desc->flags);

	if (flags & GPIOF_ACTIVE_LOW)
		set_bit(FLAG_ACTIVE_LOW, &desc->flags);

	if (flags & GPIOF_DIR_IN)
		err = gpiod_direction_input(desc);
	else
		err = gpiod_direction_output_raw(desc,
				(flags & GPIOF_INIT_HIGH) ? 1 : 0);

	if (err)
		goto free_gpio;

	if (flags & GPIOF_EXPORT) {
		err = gpiod_export(desc, flags & GPIOF_EXPORT_CHANGEABLE);
		if (err)
			goto free_gpio;
	}

	return 0;

 free_gpio:
	gpiod_free(desc);
	return err;
}