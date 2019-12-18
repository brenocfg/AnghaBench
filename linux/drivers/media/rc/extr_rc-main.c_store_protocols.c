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
typedef  scalar_t__ u64 ;
struct rc_scancode_filter {scalar_t__ mask; scalar_t__ data; } ;
struct rc_dev {scalar_t__ enabled_protocols; int (* change_protocol ) (struct rc_dev*,scalar_t__*) ;scalar_t__ driver_type; int (* s_filter ) (struct rc_dev*,struct rc_scancode_filter*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; struct rc_scancode_filter scancode_filter; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ir_raw_load_modules (scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int parse_protocol_change (struct rc_dev*,scalar_t__*,char const*) ; 
 int stub1 (struct rc_dev*,scalar_t__*) ; 
 int stub2 (struct rc_dev*,struct rc_scancode_filter*) ; 
 int stub3 (struct rc_dev*,struct rc_scancode_filter*) ; 
 struct rc_dev* to_rc_dev (struct device*) ; 

__attribute__((used)) static ssize_t store_protocols(struct device *device,
			       struct device_attribute *mattr,
			       const char *buf, size_t len)
{
	struct rc_dev *dev = to_rc_dev(device);
	u64 *current_protocols;
	struct rc_scancode_filter *filter;
	u64 old_protocols, new_protocols;
	ssize_t rc;

	dev_dbg(&dev->dev, "Normal protocol change requested\n");
	current_protocols = &dev->enabled_protocols;
	filter = &dev->scancode_filter;

	if (!dev->change_protocol) {
		dev_dbg(&dev->dev, "Protocol switching not supported\n");
		return -EINVAL;
	}

	mutex_lock(&dev->lock);

	old_protocols = *current_protocols;
	new_protocols = old_protocols;
	rc = parse_protocol_change(dev, &new_protocols, buf);
	if (rc < 0)
		goto out;

	if (dev->driver_type == RC_DRIVER_IR_RAW)
		ir_raw_load_modules(&new_protocols);

	rc = dev->change_protocol(dev, &new_protocols);
	if (rc < 0) {
		dev_dbg(&dev->dev, "Error setting protocols to 0x%llx\n",
			(long long)new_protocols);
		goto out;
	}

	if (new_protocols != old_protocols) {
		*current_protocols = new_protocols;
		dev_dbg(&dev->dev, "Protocols changed to 0x%llx\n",
			(long long)new_protocols);
	}

	/*
	 * If a protocol change was attempted the filter may need updating, even
	 * if the actual protocol mask hasn't changed (since the driver may have
	 * cleared the filter).
	 * Try setting the same filter with the new protocol (if any).
	 * Fall back to clearing the filter.
	 */
	if (dev->s_filter && filter->mask) {
		if (new_protocols)
			rc = dev->s_filter(dev, filter);
		else
			rc = -1;

		if (rc < 0) {
			filter->data = 0;
			filter->mask = 0;
			dev->s_filter(dev, filter);
		}
	}

	rc = len;

out:
	mutex_unlock(&dev->lock);
	return rc;
}