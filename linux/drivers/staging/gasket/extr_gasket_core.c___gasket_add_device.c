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
struct gasket_internal_desc {int /*<<< orphan*/  class; struct gasket_driver_desc* driver_desc; } ;
struct gasket_driver_desc {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  devt; int /*<<< orphan*/  device; int /*<<< orphan*/  name; } ;
struct gasket_dev {TYPE_1__ dev_info; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gasket_alloc_dev (struct gasket_internal_desc*,struct device*,struct gasket_dev**) ; 
 int /*<<< orphan*/  gasket_free_dev (struct gasket_dev*) ; 
 int gasket_sysfs_create_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gasket_sysfs_create_mapping (int /*<<< orphan*/ ,struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_sysfs_generic_attrs ; 
 int /*<<< orphan*/  gasket_sysfs_remove_mapping (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __gasket_add_device(struct device *parent_dev,
			       struct gasket_internal_desc *internal_desc,
			       struct gasket_dev **gasket_devp)
{
	int ret;
	struct gasket_dev *gasket_dev;
	const struct gasket_driver_desc *driver_desc =
	    internal_desc->driver_desc;

	ret = gasket_alloc_dev(internal_desc, parent_dev, &gasket_dev);
	if (ret)
		return ret;
	if (IS_ERR(gasket_dev->dev_info.device)) {
		dev_err(parent_dev, "Cannot create %s device %s [ret = %ld]\n",
			driver_desc->name, gasket_dev->dev_info.name,
			PTR_ERR(gasket_dev->dev_info.device));
		ret = -ENODEV;
		goto free_gasket_dev;
	}

	ret = gasket_sysfs_create_mapping(gasket_dev->dev_info.device,
					  gasket_dev);
	if (ret)
		goto remove_device;

	ret = gasket_sysfs_create_entries(gasket_dev->dev_info.device,
					  gasket_sysfs_generic_attrs);
	if (ret)
		goto remove_sysfs_mapping;

	*gasket_devp = gasket_dev;
	return 0;

remove_sysfs_mapping:
	gasket_sysfs_remove_mapping(gasket_dev->dev_info.device);
remove_device:
	device_destroy(internal_desc->class, gasket_dev->dev_info.devt);
free_gasket_dev:
	gasket_free_dev(gasket_dev);
	return ret;
}