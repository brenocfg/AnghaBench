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
struct gpio_chip {int /*<<< orphan*/  label; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_IS_HOGGED ; 
 int GPIOD_FLAGS_BIT_DIR_OUT ; 
 int GPIOD_FLAGS_BIT_DIR_VAL ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  desc_to_gpio (struct gpio_desc*) ; 
 int gpio_chip_hwgpio (struct gpio_desc*) ; 
 struct gpio_desc* gpiochip_request_own_desc (struct gpio_chip*,int,char const*,unsigned long,int) ; 
 struct gpio_chip* gpiod_to_chip (struct gpio_desc*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char const*,char*,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int gpiod_hog(struct gpio_desc *desc, const char *name,
	      unsigned long lflags, enum gpiod_flags dflags)
{
	struct gpio_chip *chip;
	struct gpio_desc *local_desc;
	int hwnum;
	int ret;

	chip = gpiod_to_chip(desc);
	hwnum = gpio_chip_hwgpio(desc);

	local_desc = gpiochip_request_own_desc(chip, hwnum, name,
					       lflags, dflags);
	if (IS_ERR(local_desc)) {
		ret = PTR_ERR(local_desc);
		pr_err("requesting hog GPIO %s (chip %s, offset %d) failed, %d\n",
		       name, chip->label, hwnum, ret);
		return ret;
	}

	/* Mark GPIO as hogged so it can be identified and removed later */
	set_bit(FLAG_IS_HOGGED, &desc->flags);

	pr_info("GPIO line %d (%s) hogged as %s%s\n",
		desc_to_gpio(desc), name,
		(dflags&GPIOD_FLAGS_BIT_DIR_OUT) ? "output" : "input",
		(dflags&GPIOD_FLAGS_BIT_DIR_OUT) ?
		  (dflags&GPIOD_FLAGS_BIT_DIR_VAL) ? "/high" : "/low":"");

	return 0;
}