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
struct platform_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_driver_unregister (struct platform_driver* const) ; 
 int /*<<< orphan*/  pr_debug (char*,struct platform_driver* const) ; 

void platform_unregister_drivers(struct platform_driver * const *drivers,
				 unsigned int count)
{
	while (count--) {
		pr_debug("unregistering platform driver %ps\n", drivers[count]);
		platform_driver_unregister(drivers[count]);
	}
}