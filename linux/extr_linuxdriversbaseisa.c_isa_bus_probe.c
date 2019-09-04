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
struct isa_driver {int (* probe ) (struct device*,int /*<<< orphan*/ ) ;} ;
struct device {struct isa_driver* platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int stub1 (struct device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_isa_dev (struct device*) ; 

__attribute__((used)) static int isa_bus_probe(struct device *dev)
{
	struct isa_driver *isa_driver = dev->platform_data;

	if (isa_driver && isa_driver->probe)
		return isa_driver->probe(dev, to_isa_dev(dev)->id);

	return 0;
}