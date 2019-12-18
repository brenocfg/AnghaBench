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
struct smsc47b397_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  lock; scalar_t__ addr; } ;
struct resource {scalar_t__ start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 scalar_t__ SMSC_EXTENT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long,scalar_t__) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,char*,struct smsc47b397_data*,int /*<<< orphan*/ ) ; 
 struct smsc47b397_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ smsc47b397_driver ; 
 int /*<<< orphan*/  smsc47b397_groups ; 

__attribute__((used)) static int smsc47b397_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct smsc47b397_data *data;
	struct device *hwmon_dev;
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!devm_request_region(dev, res->start, SMSC_EXTENT,
				 smsc47b397_driver.driver.name)) {
		dev_err(dev, "Region 0x%lx-0x%lx already in use!\n",
			(unsigned long)res->start,
			(unsigned long)res->start + SMSC_EXTENT - 1);
		return -EBUSY;
	}

	data = devm_kzalloc(dev, sizeof(struct smsc47b397_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->addr = res->start;
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, "smsc47b397",
							   data,
							   smsc47b397_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}