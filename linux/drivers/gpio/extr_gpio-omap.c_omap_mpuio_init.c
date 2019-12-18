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
struct gpio_bank {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_mpuio_device ; 
 int /*<<< orphan*/  omap_mpuio_driver ; 
 int /*<<< orphan*/  platform_device_register (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (int /*<<< orphan*/ *,struct gpio_bank*) ; 

__attribute__((used)) static inline void omap_mpuio_init(struct gpio_bank *bank)
{
	platform_set_drvdata(&omap_mpuio_device, bank);

	if (platform_driver_register(&omap_mpuio_driver) == 0)
		(void) platform_device_register(&omap_mpuio_device);
}