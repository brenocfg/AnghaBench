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
struct dma_slave_map {int /*<<< orphan*/  slave; int /*<<< orphan*/  devname; } ;
struct TYPE_2__ {int mapcnt; struct dma_slave_map* map; } ;
struct dma_device {TYPE_1__ filter; } ;
struct device {int dummy; } ;

/* Variables and functions */
 char const* dev_name (struct device*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct dma_slave_map *dma_filter_match(struct dma_device *device,
						    const char *name,
						    struct device *dev)
{
	int i;

	if (!device->filter.mapcnt)
		return NULL;

	for (i = 0; i < device->filter.mapcnt; i++) {
		const struct dma_slave_map *map = &device->filter.map[i];

		if (!strcmp(map->devname, dev_name(dev)) &&
		    !strcmp(map->slave, name))
			return map;
	}

	return NULL;
}