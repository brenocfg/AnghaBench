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
struct toshiba_haps_dev {int protection_level; struct acpi_device* acpi_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct acpi_device {TYPE_1__ dev; int /*<<< orphan*/  handle; struct toshiba_haps_dev* driver_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct toshiba_haps_dev*) ; 
 int /*<<< orphan*/  haps_attr_group ; 
 struct toshiba_haps_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct toshiba_haps_dev* toshiba_haps ; 
 int /*<<< orphan*/  toshiba_haps_available (int /*<<< orphan*/ ) ; 
 int toshiba_haps_protection_level (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int toshiba_haps_add(struct acpi_device *acpi_dev)
{
	struct toshiba_haps_dev *haps;
	int ret;

	if (toshiba_haps)
		return -EBUSY;

	if (!toshiba_haps_available(acpi_dev->handle))
		return -ENODEV;

	pr_info("Toshiba HDD Active Protection Sensor device\n");

	haps = kzalloc(sizeof(struct toshiba_haps_dev), GFP_KERNEL);
	if (!haps)
		return -ENOMEM;

	haps->acpi_dev = acpi_dev;
	haps->protection_level = 2;
	acpi_dev->driver_data = haps;
	dev_set_drvdata(&acpi_dev->dev, haps);

	/* Set the protection level, currently at level 2 (Medium) */
	ret = toshiba_haps_protection_level(acpi_dev->handle, 2);
	if (ret != 0)
		return ret;

	ret = sysfs_create_group(&acpi_dev->dev.kobj, &haps_attr_group);
	if (ret)
		return ret;

	toshiba_haps = haps;

	return 0;
}