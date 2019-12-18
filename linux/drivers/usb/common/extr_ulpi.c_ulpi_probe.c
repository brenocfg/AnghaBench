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
struct ulpi_driver {int (* probe ) (int /*<<< orphan*/ ) ;} ;
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int of_clk_set_defaults (int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_ulpi_dev (struct device*) ; 
 struct ulpi_driver* to_ulpi_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ulpi_probe(struct device *dev)
{
	struct ulpi_driver *drv = to_ulpi_driver(dev->driver);
	int ret;

	ret = of_clk_set_defaults(dev->of_node, false);
	if (ret < 0)
		return ret;

	return drv->probe(to_ulpi_dev(dev));
}