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
struct rmi_driver_data {int enabled; } ;
struct rmi_device_platform_data {int /*<<< orphan*/  irq; } ;
struct rmi_device {int /*<<< orphan*/  dev; TYPE_1__* xport; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  dev_driver_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct rmi_device*) ; 
 int irq_get_trigger_type (int /*<<< orphan*/ ) ; 
 struct rmi_device_platform_data* rmi_get_platform_data (struct rmi_device*) ; 
 int /*<<< orphan*/  rmi_irq_fn ; 

__attribute__((used)) static int rmi_irq_init(struct rmi_device *rmi_dev)
{
	struct rmi_device_platform_data *pdata = rmi_get_platform_data(rmi_dev);
	struct rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	int irq_flags = irq_get_trigger_type(pdata->irq);
	int ret;

	if (!irq_flags)
		irq_flags = IRQF_TRIGGER_LOW;

	ret = devm_request_threaded_irq(&rmi_dev->dev, pdata->irq, NULL,
					rmi_irq_fn, irq_flags | IRQF_ONESHOT,
					dev_driver_string(rmi_dev->xport->dev),
					rmi_dev);
	if (ret < 0) {
		dev_err(&rmi_dev->dev, "Failed to register interrupt %d\n",
			pdata->irq);

		return ret;
	}

	data->enabled = true;

	return 0;
}