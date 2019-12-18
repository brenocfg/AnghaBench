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
struct nvdimm_bus {int dummy; } ;
struct device {struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN_ONCE (struct device*,int,char*) ; 
 scalar_t__ is_nvdimm_bus (struct device*) ; 
 struct nvdimm_bus* to_nvdimm_bus (struct device*) ; 

struct nvdimm_bus *walk_to_nvdimm_bus(struct device *nd_dev)
{
	struct device *dev;

	for (dev = nd_dev; dev; dev = dev->parent)
		if (is_nvdimm_bus(dev))
			break;
	dev_WARN_ONCE(nd_dev, !dev, "invalid dev, not on nd bus\n");
	if (dev)
		return to_nvdimm_bus(dev);
	return NULL;
}