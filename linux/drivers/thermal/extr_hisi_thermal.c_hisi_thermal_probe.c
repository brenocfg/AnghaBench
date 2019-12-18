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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct hisi_thermal_sensor {int /*<<< orphan*/  irq_name; } ;
struct hisi_thermal_data {int nr_sensors; TYPE_1__* ops; struct hisi_thermal_sensor* sensor; int /*<<< orphan*/  regs; struct platform_device* pdev; } ;
struct TYPE_2__ {int (* probe ) (struct hisi_thermal_data*) ;int (* enable_sensor ) (struct hisi_thermal_sensor*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct hisi_thermal_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_thermal_sensor*) ; 
 int /*<<< orphan*/  hisi_thermal_alarm_irq_thread ; 
 int hisi_thermal_register_sensor (struct platform_device*,struct hisi_thermal_sensor*) ; 
 int /*<<< orphan*/  hisi_thermal_toggle_sensor (struct hisi_thermal_sensor*,int) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hisi_thermal_data*) ; 
 int stub1 (struct hisi_thermal_data*) ; 
 int stub2 (struct hisi_thermal_sensor*) ; 

__attribute__((used)) static int hisi_thermal_probe(struct platform_device *pdev)
{
	struct hisi_thermal_data *data;
	struct device *dev = &pdev->dev;
	struct resource *res;
	int i, ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->pdev = pdev;
	platform_set_drvdata(pdev, data);
	data->ops = of_device_get_match_data(dev);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(data->regs)) {
		dev_err(dev, "failed to get io address\n");
		return PTR_ERR(data->regs);
	}

	ret = data->ops->probe(data);
	if (ret)
		return ret;

	for (i = 0; i < data->nr_sensors; i++) {
		struct hisi_thermal_sensor *sensor = &data->sensor[i];

		ret = hisi_thermal_register_sensor(pdev, sensor);
		if (ret) {
			dev_err(dev, "failed to register thermal sensor: %d\n",
				ret);
			return ret;
		}

		ret = platform_get_irq(pdev, 0);
		if (ret < 0)
			return ret;

		ret = devm_request_threaded_irq(dev, ret, NULL,
						hisi_thermal_alarm_irq_thread,
						IRQF_ONESHOT, sensor->irq_name,
						sensor);
		if (ret < 0) {
			dev_err(dev, "Failed to request alarm irq: %d\n", ret);
			return ret;
		}

		ret = data->ops->enable_sensor(sensor);
		if (ret) {
			dev_err(dev, "Failed to setup the sensor: %d\n", ret);
			return ret;
		}

		hisi_thermal_toggle_sensor(sensor, true);
	}

	return 0;
}