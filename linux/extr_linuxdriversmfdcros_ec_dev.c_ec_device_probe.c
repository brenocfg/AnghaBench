#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  id; struct device dev; } ;
struct cros_ec_platform {int /*<<< orphan*/  ec_name; int /*<<< orphan*/  cmd_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/ * class; int /*<<< orphan*/  devt; } ;
struct cros_ec_dev {unsigned int* features; TYPE_1__ class_dev; int /*<<< orphan*/  cdev; struct device* dev; int /*<<< orphan*/  cmd_offset; int /*<<< orphan*/  ec_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_FEATURE_CEC ; 
 int /*<<< orphan*/  EC_FEATURE_MOTION_SENSE ; 
 int /*<<< orphan*/  EC_FEATURE_RTC ; 
 int /*<<< orphan*/  EC_FEATURE_USB_PD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cros_class ; 
 int /*<<< orphan*/  cros_ec_cec_cells ; 
 scalar_t__ cros_ec_check_features (struct cros_ec_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cros_ec_class_release ; 
 scalar_t__ cros_ec_debugfs_init (struct cros_ec_dev*) ; 
 int /*<<< orphan*/  cros_ec_rtc_cells ; 
 int /*<<< orphan*/  cros_ec_sensors_register (struct cros_ec_dev*) ; 
 int /*<<< orphan*/  cros_usbpd_charger_cells ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_platform* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct cros_ec_dev*) ; 
 int dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  ec_major ; 
 int /*<<< orphan*/  fops ; 
 struct cros_ec_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lb_manual_suspend_ctrl (struct cros_ec_dev*,int) ; 
 int mfd_add_devices (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static int ec_device_probe(struct platform_device *pdev)
{
	int retval = -ENOMEM;
	struct device *dev = &pdev->dev;
	struct cros_ec_platform *ec_platform = dev_get_platdata(dev);
	struct cros_ec_dev *ec = kzalloc(sizeof(*ec), GFP_KERNEL);

	if (!ec)
		return retval;

	dev_set_drvdata(dev, ec);
	ec->ec_dev = dev_get_drvdata(dev->parent);
	ec->dev = dev;
	ec->cmd_offset = ec_platform->cmd_offset;
	ec->features[0] = -1U; /* Not cached yet */
	ec->features[1] = -1U; /* Not cached yet */
	device_initialize(&ec->class_dev);
	cdev_init(&ec->cdev, &fops);

	/*
	 * Add the class device
	 * Link to the character device for creating the /dev entry
	 * in devtmpfs.
	 */
	ec->class_dev.devt = MKDEV(ec_major, pdev->id);
	ec->class_dev.class = &cros_class;
	ec->class_dev.parent = dev;
	ec->class_dev.release = cros_ec_class_release;

	retval = dev_set_name(&ec->class_dev, "%s", ec_platform->ec_name);
	if (retval) {
		dev_err(dev, "dev_set_name failed => %d\n", retval);
		goto failed;
	}

	/* check whether this EC is a sensor hub. */
	if (cros_ec_check_features(ec, EC_FEATURE_MOTION_SENSE))
		cros_ec_sensors_register(ec);

	/* Check whether this EC instance has CEC host command support */
	if (cros_ec_check_features(ec, EC_FEATURE_CEC)) {
		retval = mfd_add_devices(ec->dev, PLATFORM_DEVID_AUTO,
					 cros_ec_cec_cells,
					 ARRAY_SIZE(cros_ec_cec_cells),
					 NULL, 0, NULL);
		if (retval)
			dev_err(ec->dev,
				"failed to add cros-ec-cec device: %d\n",
				retval);
	}

	/* Check whether this EC instance has RTC host command support */
	if (cros_ec_check_features(ec, EC_FEATURE_RTC)) {
		retval = mfd_add_devices(ec->dev, PLATFORM_DEVID_AUTO,
					 cros_ec_rtc_cells,
					 ARRAY_SIZE(cros_ec_rtc_cells),
					 NULL, 0, NULL);
		if (retval)
			dev_err(ec->dev,
				"failed to add cros-ec-rtc device: %d\n",
				retval);
	}

	/* Check whether this EC instance has the PD charge manager */
	if (cros_ec_check_features(ec, EC_FEATURE_USB_PD)) {
		retval = mfd_add_devices(ec->dev, PLATFORM_DEVID_AUTO,
					 cros_usbpd_charger_cells,
					 ARRAY_SIZE(cros_usbpd_charger_cells),
					 NULL, 0, NULL);
		if (retval)
			dev_err(ec->dev,
				"failed to add cros-usbpd-charger device: %d\n",
				retval);
	}

	/* Take control of the lightbar from the EC. */
	lb_manual_suspend_ctrl(ec, 1);

	/* We can now add the sysfs class, we know which parameter to show */
	retval = cdev_device_add(&ec->cdev, &ec->class_dev);
	if (retval) {
		dev_err(dev, "cdev_device_add failed => %d\n", retval);
		goto failed;
	}

	if (cros_ec_debugfs_init(ec))
		dev_warn(dev, "failed to create debugfs directory\n");

	return 0;

failed:
	put_device(&ec->class_dev);
	return retval;
}