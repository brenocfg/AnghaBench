#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; scalar_t__ start; } ;
struct platform_device {int num_resources; struct resource* resource; } ;
struct TYPE_4__ {scalar_t__ mapbase; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int NR_PORTS ; 
 TYPE_2__* sa1100_ports ; 
 int /*<<< orphan*/  sa1100_serial_add_one_port (TYPE_2__*,struct platform_device*) ; 

__attribute__((used)) static int sa1100_serial_probe(struct platform_device *dev)
{
	struct resource *res = dev->resource;
	int i;

	for (i = 0; i < dev->num_resources; i++, res++)
		if (res->flags & IORESOURCE_MEM)
			break;

	if (i < dev->num_resources) {
		for (i = 0; i < NR_PORTS; i++) {
			if (sa1100_ports[i].port.mapbase != res->start)
				continue;

			sa1100_serial_add_one_port(&sa1100_ports[i], dev);
			break;
		}
	}

	return 0;
}