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
struct ec_response_get_protocol_info {int dummy; } ;
struct ec_params_hello {int dummy; } ;
struct device {scalar_t__ of_node; } ;
struct cros_ec_device {int max_request; int max_response; int irq; struct device* dev; scalar_t__ max_passthru; int /*<<< orphan*/  lock; void* dout; int /*<<< orphan*/  dout_size; void* din; int /*<<< orphan*/  din_size; int /*<<< orphan*/  event_notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int cros_ec_query_all (struct cros_ec_device*) ; 
 int cros_ec_sleep_event (struct cros_ec_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (struct device*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct cros_ec_device*) ; 
 int /*<<< orphan*/  ec_cell ; 
 int /*<<< orphan*/  ec_irq_thread ; 
 int /*<<< orphan*/  ec_pd_cell ; 
 int mfd_add_devices (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (struct device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int cros_ec_register(struct cros_ec_device *ec_dev)
{
	struct device *dev = ec_dev->dev;
	int err = 0;

	BLOCKING_INIT_NOTIFIER_HEAD(&ec_dev->event_notifier);

	ec_dev->max_request = sizeof(struct ec_params_hello);
	ec_dev->max_response = sizeof(struct ec_response_get_protocol_info);
	ec_dev->max_passthru = 0;

	ec_dev->din = devm_kzalloc(dev, ec_dev->din_size, GFP_KERNEL);
	if (!ec_dev->din)
		return -ENOMEM;

	ec_dev->dout = devm_kzalloc(dev, ec_dev->dout_size, GFP_KERNEL);
	if (!ec_dev->dout)
		return -ENOMEM;

	mutex_init(&ec_dev->lock);

	err = cros_ec_query_all(ec_dev);
	if (err) {
		dev_err(dev, "Cannot identify the EC: error %d\n", err);
		return err;
	}

	if (ec_dev->irq) {
		err = devm_request_threaded_irq(dev, ec_dev->irq, NULL,
				ec_irq_thread, IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				"chromeos-ec", ec_dev);
		if (err) {
			dev_err(dev, "Failed to request IRQ %d: %d",
				ec_dev->irq, err);
			return err;
		}
	}

	err = mfd_add_devices(ec_dev->dev, PLATFORM_DEVID_AUTO, &ec_cell, 1,
			      NULL, ec_dev->irq, NULL);
	if (err) {
		dev_err(dev,
			"Failed to register Embedded Controller subdevice %d\n",
			err);
		return err;
	}

	if (ec_dev->max_passthru) {
		/*
		 * Register a PD device as well on top of this device.
		 * We make the following assumptions:
		 * - behind an EC, we have a pd
		 * - only one device added.
		 * - the EC is responsive at init time (it is not true for a
		 *   sensor hub.
		 */
		err = mfd_add_devices(ec_dev->dev, PLATFORM_DEVID_AUTO,
				      &ec_pd_cell, 1, NULL, ec_dev->irq, NULL);
		if (err) {
			dev_err(dev,
				"Failed to register Power Delivery subdevice %d\n",
				err);
			return err;
		}
	}

	if (IS_ENABLED(CONFIG_OF) && dev->of_node) {
		err = devm_of_platform_populate(dev);
		if (err) {
			mfd_remove_devices(dev);
			dev_err(dev, "Failed to register sub-devices\n");
			return err;
		}
	}

	/*
	 * Clear sleep event - this will fail harmlessly on platforms that
	 * don't implement the sleep event host command.
	 */
	err = cros_ec_sleep_event(ec_dev, 0);
	if (err < 0)
		dev_dbg(ec_dev->dev, "Error %d clearing sleep event to ec",
			err);

	dev_info(dev, "Chrome EC device registered\n");

	return 0;
}