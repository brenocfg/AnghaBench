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
struct TYPE_2__ {struct device_driver* driver; } ;
struct pardevice {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct device_driver {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pp_probe(struct pardevice *par_dev)
{
	struct device_driver *drv = par_dev->dev.driver;
	int len = strlen(drv->name);

	if (strncmp(par_dev->name, drv->name, len))
		return -ENODEV;

	return 0;
}