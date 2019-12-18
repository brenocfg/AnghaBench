#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct gasket_sysfs_mapping {struct gasket_dev* gasket_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  bar; } ;
struct TYPE_4__ {TYPE_1__ bar_address; } ;
struct gasket_sysfs_attribute {int /*<<< orphan*/  (* write_callback ) (struct gasket_dev*,struct gasket_sysfs_attribute*,int /*<<< orphan*/ ) ;TYPE_2__ data; } ;
struct gasket_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  gasket_dev_write_64 (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gasket_sysfs_attribute* gasket_sysfs_get_attr (struct device*,struct device_attribute*) ; 
 int /*<<< orphan*/  gasket_sysfs_put_attr (struct device*,struct gasket_sysfs_attribute*) ; 
 struct gasket_sysfs_mapping* get_mapping (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_mapping (struct gasket_sysfs_mapping*) ; 
 int /*<<< orphan*/  stub1 (struct gasket_dev*,struct gasket_sysfs_attribute*,int /*<<< orphan*/ ) ; 

ssize_t gasket_sysfs_register_store(struct device *device,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	ulong parsed_value = 0;
	struct gasket_sysfs_mapping *mapping;
	struct gasket_dev *gasket_dev;
	struct gasket_sysfs_attribute *gasket_attr;

	if (count < 3 || buf[0] != '0' || buf[1] != 'x') {
		dev_err(device,
			"sysfs register write format: \"0x<hex value>\"\n");
		return -EINVAL;
	}

	if (kstrtoul(buf, 16, &parsed_value) != 0) {
		dev_err(device,
			"Unable to parse input as 64-bit hex value: %s\n", buf);
		return -EINVAL;
	}

	mapping = get_mapping(device);
	if (!mapping) {
		dev_err(device, "Device driver may have been removed\n");
		return 0;
	}

	gasket_dev = mapping->gasket_dev;
	if (!gasket_dev) {
		dev_err(device, "Device driver may have been removed\n");
		return 0;
	}

	gasket_attr = gasket_sysfs_get_attr(device, attr);
	if (!gasket_attr) {
		put_mapping(mapping);
		return count;
	}

	gasket_dev_write_64(gasket_dev, parsed_value,
			    gasket_attr->data.bar_address.bar,
			    gasket_attr->data.bar_address.offset);

	if (gasket_attr->write_callback)
		gasket_attr->write_callback(gasket_dev, gasket_attr,
					    parsed_value);

	gasket_sysfs_put_attr(device, gasket_attr);
	put_mapping(mapping);
	return count;
}