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
struct kernfs_node {int dummy; } ;
struct TYPE_2__ {struct kernfs_node* sd; } ;
struct device {TYPE_1__ kobj; } ;
struct acpi_nfit_desc {void* scrub_count_state; int /*<<< orphan*/  nvdimm_bus; struct device* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ars_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* sysfs_get_dirent (struct kernfs_node*,char*) ; 
 int /*<<< orphan*/  sysfs_put (struct kernfs_node*) ; 
 struct device* to_nvdimm_bus_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_nfit_desc_init_scrub_attr(struct acpi_nfit_desc *acpi_desc)
{
	struct device *dev = acpi_desc->dev;
	struct kernfs_node *nfit;
	struct device *bus_dev;

	if (!ars_supported(acpi_desc->nvdimm_bus))
		return 0;

	bus_dev = to_nvdimm_bus_dev(acpi_desc->nvdimm_bus);
	nfit = sysfs_get_dirent(bus_dev->kobj.sd, "nfit");
	if (!nfit) {
		dev_err(dev, "sysfs_get_dirent 'nfit' failed\n");
		return -ENODEV;
	}
	acpi_desc->scrub_count_state = sysfs_get_dirent(nfit, "scrub");
	sysfs_put(nfit);
	if (!acpi_desc->scrub_count_state) {
		dev_err(dev, "sysfs_get_dirent 'scrub' failed\n");
		return -ENODEV;
	}

	return 0;
}