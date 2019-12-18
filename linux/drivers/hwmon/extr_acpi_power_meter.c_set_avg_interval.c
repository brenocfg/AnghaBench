#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long value; } ;
union acpi_object {TYPE_2__ integer; int /*<<< orphan*/  member_0; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {unsigned long max_avg_interval; unsigned long min_avg_interval; } ;
struct acpi_power_meter_resource {unsigned long avg_interval; int /*<<< orphan*/  lock; TYPE_3__* acpi_dev; TYPE_1__ caps; } ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
struct acpi_device {struct acpi_power_meter_resource* driver_data; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,struct acpi_object_list*,unsigned long long*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t set_avg_interval(struct device *dev,
				struct device_attribute *devattr,
				const char *buf, size_t count)
{
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_power_meter_resource *resource = acpi_dev->driver_data;
	union acpi_object arg0 = { ACPI_TYPE_INTEGER };
	struct acpi_object_list args = { 1, &arg0 };
	int res;
	unsigned long temp;
	unsigned long long data;
	acpi_status status;

	res = kstrtoul(buf, 10, &temp);
	if (res)
		return res;

	if (temp > resource->caps.max_avg_interval ||
	    temp < resource->caps.min_avg_interval)
		return -EINVAL;
	arg0.integer.value = temp;

	mutex_lock(&resource->lock);
	status = acpi_evaluate_integer(resource->acpi_dev->handle, "_PAI",
				       &args, &data);
	if (!ACPI_FAILURE(status))
		resource->avg_interval = temp;
	mutex_unlock(&resource->lock);

	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Evaluating _PAI"));
		return -EINVAL;
	}

	/* _PAI returns 0 on success, nonzero otherwise */
	if (data)
		return -EINVAL;

	return count;
}