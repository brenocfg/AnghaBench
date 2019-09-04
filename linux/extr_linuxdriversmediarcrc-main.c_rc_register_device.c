#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/ ** groups; } ;
struct rc_dev {int minor; scalar_t__ driver_type; int registered; scalar_t__ allowed_protocols; char* driver_name; int /*<<< orphan*/  rc_map; TYPE_1__ dev; scalar_t__ device_name; int /*<<< orphan*/ ** sysfs_groups; scalar_t__ s_wakeup_filter; scalar_t__ s_filter; int /*<<< orphan*/  change_protocol; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RC_DEV_MAX ; 
 scalar_t__ RC_DRIVER_IR_RAW ; 
 scalar_t__ RC_DRIVER_IR_RAW_TX ; 
 scalar_t__ RC_DRIVER_SCANCODE ; 
 scalar_t__ RC_PROTO_BIT_CEC ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,char*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct rc_dev*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_del (TYPE_1__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ir_free_table (int /*<<< orphan*/ *) ; 
 int ir_lirc_register (struct rc_dev*) ; 
 int /*<<< orphan*/  ir_lirc_unregister (struct rc_dev*) ; 
 int /*<<< orphan*/  ir_raw_event_free (struct rc_dev*) ; 
 int ir_raw_event_prepare (struct rc_dev*) ; 
 int ir_raw_event_register (struct rc_dev*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 char* kobject_get_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_dev_filter_attr_grp ; 
 int /*<<< orphan*/  rc_dev_ro_protocol_attr_grp ; 
 int /*<<< orphan*/  rc_dev_rw_protocol_attr_grp ; 
 int /*<<< orphan*/  rc_dev_wakeup_filter_attr_grp ; 
 int /*<<< orphan*/  rc_free_rx_device (struct rc_dev*) ; 
 int /*<<< orphan*/  rc_ida ; 
 int rc_prepare_rx_device (struct rc_dev*) ; 
 int rc_setup_rx_device (struct rc_dev*) ; 

int rc_register_device(struct rc_dev *dev)
{
	const char *path;
	int attr = 0;
	int minor;
	int rc;

	if (!dev)
		return -EINVAL;

	minor = ida_simple_get(&rc_ida, 0, RC_DEV_MAX, GFP_KERNEL);
	if (minor < 0)
		return minor;

	dev->minor = minor;
	dev_set_name(&dev->dev, "rc%u", dev->minor);
	dev_set_drvdata(&dev->dev, dev);

	dev->dev.groups = dev->sysfs_groups;
	if (dev->driver_type == RC_DRIVER_SCANCODE && !dev->change_protocol)
		dev->sysfs_groups[attr++] = &rc_dev_ro_protocol_attr_grp;
	else if (dev->driver_type != RC_DRIVER_IR_RAW_TX)
		dev->sysfs_groups[attr++] = &rc_dev_rw_protocol_attr_grp;
	if (dev->s_filter)
		dev->sysfs_groups[attr++] = &rc_dev_filter_attr_grp;
	if (dev->s_wakeup_filter)
		dev->sysfs_groups[attr++] = &rc_dev_wakeup_filter_attr_grp;
	dev->sysfs_groups[attr++] = NULL;

	if (dev->driver_type == RC_DRIVER_IR_RAW) {
		rc = ir_raw_event_prepare(dev);
		if (rc < 0)
			goto out_minor;
	}

	if (dev->driver_type != RC_DRIVER_IR_RAW_TX) {
		rc = rc_prepare_rx_device(dev);
		if (rc)
			goto out_raw;
	}

	rc = device_add(&dev->dev);
	if (rc)
		goto out_rx_free;

	path = kobject_get_path(&dev->dev.kobj, GFP_KERNEL);
	dev_info(&dev->dev, "%s as %s\n",
		 dev->device_name ?: "Unspecified device", path ?: "N/A");
	kfree(path);

	dev->registered = true;

	if (dev->driver_type != RC_DRIVER_IR_RAW_TX) {
		rc = rc_setup_rx_device(dev);
		if (rc)
			goto out_dev;
	}

	/* Ensure that the lirc kfifo is setup before we start the thread */
	if (dev->allowed_protocols != RC_PROTO_BIT_CEC) {
		rc = ir_lirc_register(dev);
		if (rc < 0)
			goto out_rx;
	}

	if (dev->driver_type == RC_DRIVER_IR_RAW) {
		rc = ir_raw_event_register(dev);
		if (rc < 0)
			goto out_lirc;
	}

	dev_dbg(&dev->dev, "Registered rc%u (driver: %s)\n", dev->minor,
		dev->driver_name ? dev->driver_name : "unknown");

	return 0;

out_lirc:
	if (dev->allowed_protocols != RC_PROTO_BIT_CEC)
		ir_lirc_unregister(dev);
out_rx:
	rc_free_rx_device(dev);
out_dev:
	device_del(&dev->dev);
out_rx_free:
	ir_free_table(&dev->rc_map);
out_raw:
	ir_raw_event_free(dev);
out_minor:
	ida_simple_remove(&rc_ida, minor);
	return rc;
}