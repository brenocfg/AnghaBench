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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICH7_GPIO_SIZE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/ * gp_gpio_resource ; 
 int /*<<< orphan*/  nas_gpio_io_base ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ich7_lpc_cleanup(struct device *dev)
{
	/*
	 * If we were given exclusive use of the GPIO
	 * I/O Address range, we must return it.
	 */
	if (gp_gpio_resource) {
		dev_dbg(dev, ": Releasing GPIO I/O addresses\n");
		release_region(nas_gpio_io_base, ICH7_GPIO_SIZE);
		gp_gpio_resource = NULL;
	}
}