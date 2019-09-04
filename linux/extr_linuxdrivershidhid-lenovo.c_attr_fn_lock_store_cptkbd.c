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
struct lenovo_drvdata_cptkbd {int fn_lock; } ;
struct hid_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct lenovo_drvdata_cptkbd* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ kstrtoint (char const*,int,int*) ; 
 int /*<<< orphan*/  lenovo_features_set_cptkbd (struct hid_device*) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static ssize_t attr_fn_lock_store_cptkbd(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t count)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct lenovo_drvdata_cptkbd *cptkbd_data = hid_get_drvdata(hdev);
	int value;

	if (kstrtoint(buf, 10, &value))
		return -EINVAL;
	if (value < 0 || value > 1)
		return -EINVAL;

	cptkbd_data->fn_lock = !!value;
	lenovo_features_set_cptkbd(hdev);

	return count;
}