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
struct nvdimm_bus {struct device dev; } ;

/* Variables and functions */

struct device *to_nvdimm_bus_dev(struct nvdimm_bus *nvdimm_bus)
{
	/* struct nvdimm_bus definition is private to libnvdimm */
	return &nvdimm_bus->dev;
}