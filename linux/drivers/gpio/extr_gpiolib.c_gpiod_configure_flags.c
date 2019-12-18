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
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLAG_ACTIVE_LOW ; 
 int /*<<< orphan*/  FLAG_OPEN_DRAIN ; 
 int /*<<< orphan*/  FLAG_OPEN_SOURCE ; 
 int /*<<< orphan*/  FLAG_PULL_DOWN ; 
 int /*<<< orphan*/  FLAG_PULL_UP ; 
 int GPIOD_FLAGS_BIT_DIR_OUT ; 
 int GPIOD_FLAGS_BIT_DIR_SET ; 
 int GPIOD_FLAGS_BIT_DIR_VAL ; 
 int GPIOD_FLAGS_BIT_OPEN_DRAIN ; 
 unsigned long GPIO_ACTIVE_LOW ; 
 unsigned long GPIO_OPEN_DRAIN ; 
 unsigned long GPIO_OPEN_SOURCE ; 
 unsigned long GPIO_PULL_DOWN ; 
 unsigned long GPIO_PULL_UP ; 
 unsigned long GPIO_TRANSITORY ; 
 int gpiod_direction_input (struct gpio_desc*) ; 
 int gpiod_direction_output (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  gpiod_err (struct gpio_desc*,char*) ; 
 int gpiod_set_transitory (struct gpio_desc*,unsigned long) ; 
 int /*<<< orphan*/  gpiod_warn (struct gpio_desc*,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int gpiod_configure_flags(struct gpio_desc *desc, const char *con_id,
		unsigned long lflags, enum gpiod_flags dflags)
{
	int ret;

	if (lflags & GPIO_ACTIVE_LOW)
		set_bit(FLAG_ACTIVE_LOW, &desc->flags);

	if (lflags & GPIO_OPEN_DRAIN)
		set_bit(FLAG_OPEN_DRAIN, &desc->flags);
	else if (dflags & GPIOD_FLAGS_BIT_OPEN_DRAIN) {
		/*
		 * This enforces open drain mode from the consumer side.
		 * This is necessary for some busses like I2C, but the lookup
		 * should *REALLY* have specified them as open drain in the
		 * first place, so print a little warning here.
		 */
		set_bit(FLAG_OPEN_DRAIN, &desc->flags);
		gpiod_warn(desc,
			   "enforced open drain please flag it properly in DT/ACPI DSDT/board file\n");
	}

	if (lflags & GPIO_OPEN_SOURCE)
		set_bit(FLAG_OPEN_SOURCE, &desc->flags);

	if ((lflags & GPIO_PULL_UP) && (lflags & GPIO_PULL_DOWN)) {
		gpiod_err(desc,
			  "both pull-up and pull-down enabled, invalid configuration\n");
		return -EINVAL;
	}

	if (lflags & GPIO_PULL_UP)
		set_bit(FLAG_PULL_UP, &desc->flags);
	else if (lflags & GPIO_PULL_DOWN)
		set_bit(FLAG_PULL_DOWN, &desc->flags);

	ret = gpiod_set_transitory(desc, (lflags & GPIO_TRANSITORY));
	if (ret < 0)
		return ret;

	/* No particular flag request, return here... */
	if (!(dflags & GPIOD_FLAGS_BIT_DIR_SET)) {
		pr_debug("no flags found for %s\n", con_id);
		return 0;
	}

	/* Process flags */
	if (dflags & GPIOD_FLAGS_BIT_DIR_OUT)
		ret = gpiod_direction_output(desc,
				!!(dflags & GPIOD_FLAGS_BIT_DIR_VAL));
	else
		ret = gpiod_direction_input(desc);

	return ret;
}