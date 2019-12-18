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
struct hwmon_chip_info {int dummy; } ;
struct device {int dummy; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  devm_hwmon_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct device**) ; 
 struct device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct device**) ; 
 struct device* hwmon_device_register_with_info (struct device*,char const*,void*,struct hwmon_chip_info const*,struct attribute_group const**) ; 

struct device *
devm_hwmon_device_register_with_info(struct device *dev, const char *name,
				     void *drvdata,
				     const struct hwmon_chip_info *chip,
				     const struct attribute_group **groups)
{
	struct device **ptr, *hwdev;

	if (!dev)
		return ERR_PTR(-EINVAL);

	ptr = devres_alloc(devm_hwmon_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	hwdev = hwmon_device_register_with_info(dev, name, drvdata, chip,
						groups);
	if (IS_ERR(hwdev))
		goto error;

	*ptr = hwdev;
	devres_add(dev, ptr);

	return hwdev;

error:
	devres_free(ptr);
	return hwdev;
}