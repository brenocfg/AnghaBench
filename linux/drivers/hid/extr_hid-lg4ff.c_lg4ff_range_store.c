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
typedef  scalar_t__ u16 ;
struct lg_drv_data {struct lg4ff_device_entry* device_props; } ;
struct TYPE_2__ {scalar_t__ max_range; scalar_t__ min_range; scalar_t__ range; int /*<<< orphan*/  (* set_range ) (struct hid_device*,scalar_t__) ;} ;
struct lg4ff_device_entry {TYPE_1__ wdata; } ;
struct hid_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct lg_drv_data* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct hid_device*,scalar_t__) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static ssize_t lg4ff_range_store(struct device *dev, struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct hid_device *hid = to_hid_device(dev);
	struct lg4ff_device_entry *entry;
	struct lg_drv_data *drv_data;
	u16 range = simple_strtoul(buf, NULL, 10);

	drv_data = hid_get_drvdata(hid);
	if (!drv_data) {
		hid_err(hid, "Private driver data not found!\n");
		return -EINVAL;
	}

	entry = drv_data->device_props;
	if (!entry) {
		hid_err(hid, "Device properties not found!\n");
		return -EINVAL;
	}

	if (range == 0)
		range = entry->wdata.max_range;

	/* Check if the wheel supports range setting
	 * and that the range is within limits for the wheel */
	if (entry->wdata.set_range && range >= entry->wdata.min_range && range <= entry->wdata.max_range) {
		entry->wdata.set_range(hid, range);
		entry->wdata.range = range;
	}

	return count;
}