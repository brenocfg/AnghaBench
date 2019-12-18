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
struct ulpi_driver {int /*<<< orphan*/  (* remove ) (int /*<<< orphan*/ ) ;} ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_ulpi_dev (struct device*) ; 
 struct ulpi_driver* to_ulpi_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ulpi_remove(struct device *dev)
{
	struct ulpi_driver *drv = to_ulpi_driver(dev->driver);

	if (drv->remove)
		drv->remove(to_ulpi_dev(dev));

	return 0;
}