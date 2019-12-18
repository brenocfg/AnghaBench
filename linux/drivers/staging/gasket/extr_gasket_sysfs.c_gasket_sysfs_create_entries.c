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
struct gasket_sysfs_mapping {size_t attribute_count; int /*<<< orphan*/  mutex; struct gasket_sysfs_attribute* attributes; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct gasket_sysfs_attribute {TYPE_2__ attr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GASKET_ARRAY_END_MARKER ; 
 size_t GASKET_SYSFS_MAX_NODES ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int device_create_file (struct device*,TYPE_2__*) ; 
 struct gasket_sysfs_mapping* get_mapping (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_mapping (struct gasket_sysfs_mapping*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gasket_sysfs_create_entries(struct device *device,
				const struct gasket_sysfs_attribute *attrs)
{
	int i;
	int ret;
	struct gasket_sysfs_mapping *mapping = get_mapping(device);

	if (!mapping) {
		dev_dbg(device,
			"Creating entries for device without first initializing mapping\n");
		return -EINVAL;
	}

	mutex_lock(&mapping->mutex);
	for (i = 0; strcmp(attrs[i].attr.attr.name, GASKET_ARRAY_END_MARKER);
		i++) {
		if (mapping->attribute_count == GASKET_SYSFS_MAX_NODES) {
			dev_err(device,
				"Maximum number of sysfs nodes reached for device\n");
			mutex_unlock(&mapping->mutex);
			put_mapping(mapping);
			return -ENOMEM;
		}

		ret = device_create_file(device, &attrs[i].attr);
		if (ret) {
			dev_dbg(device, "Unable to create device entries\n");
			mutex_unlock(&mapping->mutex);
			put_mapping(mapping);
			return ret;
		}

		mapping->attributes[mapping->attribute_count] = attrs[i];
		++mapping->attribute_count;
	}

	mutex_unlock(&mapping->mutex);
	put_mapping(mapping);
	return 0;
}