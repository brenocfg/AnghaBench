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
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int EINVAL ; 
 int GPIOD_FLAGS_BIT_DIR_OUT ; 
 int GPIOD_FLAGS_BIT_DIR_SET ; 
 int GPIOD_FLAGS_BIT_DIR_VAL ; 

__attribute__((used)) static int
__acpi_gpio_update_gpiod_flags(enum gpiod_flags *flags, enum gpiod_flags update)
{
	int ret = 0;

	/*
	 * Check if the BIOS has IoRestriction with explicitly set direction
	 * and update @flags accordingly. Otherwise use whatever caller asked
	 * for.
	 */
	if (update & GPIOD_FLAGS_BIT_DIR_SET) {
		enum gpiod_flags diff = *flags ^ update;

		/*
		 * Check if caller supplied incompatible GPIO initialization
		 * flags.
		 *
		 * Return %-EINVAL to notify that firmware has different
		 * settings and we are going to use them.
		 */
		if (((*flags & GPIOD_FLAGS_BIT_DIR_SET) && (diff & GPIOD_FLAGS_BIT_DIR_OUT)) ||
		    ((*flags & GPIOD_FLAGS_BIT_DIR_OUT) && (diff & GPIOD_FLAGS_BIT_DIR_VAL)))
			ret = -EINVAL;
		*flags = update;
	}
	return ret;
}