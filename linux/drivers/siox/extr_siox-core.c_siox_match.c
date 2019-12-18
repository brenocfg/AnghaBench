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
struct device_driver {int dummy; } ;
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  siox_device_type ; 

__attribute__((used)) static int siox_match(struct device *dev, struct device_driver *drv)
{
	if (dev->type != &siox_device_type)
		return 0;

	/* up to now there is only a single driver so keeping this simple */
	return 1;
}