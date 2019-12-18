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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct logger_data {int /*<<< orphan*/  log_work; int /*<<< orphan*/  log_workqueue; struct cros_ec_dev* ec_dev; struct device* dev; } ;
struct cros_ec_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CROS_USBPD_LOG_UPDATE_DELAY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  cros_usbpd_log_check ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct logger_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct logger_data*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cros_usbpd_logger_probe(struct platform_device *pd)
{
	struct cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);
	struct device *dev = &pd->dev;
	struct logger_data *logger;

	logger = devm_kzalloc(dev, sizeof(*logger), GFP_KERNEL);
	if (!logger)
		return -ENOMEM;

	logger->dev = dev;
	logger->ec_dev = ec_dev;

	platform_set_drvdata(pd, logger);

	/* Retrieve PD event logs periodically */
	INIT_DELAYED_WORK(&logger->log_work, cros_usbpd_log_check);
	logger->log_workqueue =	create_singlethread_workqueue("cros_usbpd_log");
	if (!logger->log_workqueue)
		return -ENOMEM;

	queue_delayed_work(logger->log_workqueue, &logger->log_work,
			   CROS_USBPD_LOG_UPDATE_DELAY);

	return 0;
}