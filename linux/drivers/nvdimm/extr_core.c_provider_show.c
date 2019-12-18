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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* nvdimm_bus_provider (struct nvdimm_bus*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct nvdimm_bus* to_nvdimm_bus (struct device*) ; 

__attribute__((used)) static ssize_t provider_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);

	return sprintf(buf, "%s\n", nvdimm_bus_provider(nvdimm_bus));
}