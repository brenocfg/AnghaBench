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
struct nd_region_data {int ns_active; int ns_count; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 struct nd_region_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t init_namespaces_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_region_data *ndrd = dev_get_drvdata(dev);
	ssize_t rc;

	nvdimm_bus_lock(dev);
	if (ndrd)
		rc = sprintf(buf, "%d/%d\n", ndrd->ns_active, ndrd->ns_count);
	else
		rc = -ENXIO;
	nvdimm_bus_unlock(dev);

	return rc;
}