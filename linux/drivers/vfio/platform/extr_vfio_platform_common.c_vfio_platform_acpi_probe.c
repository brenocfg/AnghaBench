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
struct vfio_platform_device {int /*<<< orphan*/  acpihid; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  acpi_device_hid (struct acpi_device*) ; 
 scalar_t__ acpi_disabled ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfio_platform_acpi_probe(struct vfio_platform_device *vdev,
				    struct device *dev)
{
	struct acpi_device *adev;

	if (acpi_disabled)
		return -ENOENT;

	adev = ACPI_COMPANION(dev);
	if (!adev) {
		dev_err(dev, "ACPI companion device not found for %s\n",
			vdev->name);
		return -ENODEV;
	}

#ifdef CONFIG_ACPI
	vdev->acpihid = acpi_device_hid(adev);
#endif
	return WARN_ON(!vdev->acpihid) ? -EINVAL : 0;
}