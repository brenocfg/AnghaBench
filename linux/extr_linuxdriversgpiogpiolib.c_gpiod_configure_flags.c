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
 int /*<<< orphan*/  FLAG_ACTIVE_LOW ; 
 int /*<<< orphan*/  FLAG_OPEN_DRAIN ; 
 int /*<<< orphan*/  FLAG_OPEN_SOURCE ; 
 int GPIOD_FLAGS_BIT_DIR_OUT ; 
 int GPIOD_FLAGS_BIT_DIR_SET ; 
 int GPIOD_FLAGS_BIT_DIR_VAL ; 
 int GPIOD_FLAGS_BIT_OPEN_DRAIN ; 
 unsigned long GPIO_ACTIVE_LOW ; 
 unsigned long GPIO_OPEN_DRAIN ; 
 unsigned long GPIO_OPEN_SOURCE ; 
 unsigned long GPIO_TRANSITORY ; 
 int gpiod_direction_input (struct gpio_desc*) ; 
 int gpiod_direction_output (struct gpio_desc*,int) ; 
 int gpiod_set_transitory (struct gpio_desc*,unsigned long) ; 
 int /*<<< orphan*/  gpiod_warn (struct gpio_desc*,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int gpiod_configure_flags(struct gpio_desc *desc, const char *con_id,
		unsigned long lflags, enum gpiod_flags dflags)
{
	int status;

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

	status = gpiod_set_transitory(desc, (lflags & GPIO_TRANSITORY));
	if (status < 0)
		return status;

	/* No particular flag request, return here... */
	if (!(dflags & GPIOD_FLAGS_BIT_DIR_SET)) {
		pr_debug("no flags found for %s\n", con_id);
		return 0;
	}

	/* Process flags */
	if (dflags & GPIOD_FLAGS_BIT_DIR_OUT)
		status = gpiod_direction_output(desc,
				!!(dflags & GPIOD_FLAGS_BIT_DIR_VAL));
	else
		status = gpiod_direction_input(desc);

	return status;
}