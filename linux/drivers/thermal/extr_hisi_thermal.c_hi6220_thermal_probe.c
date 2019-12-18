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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct hisi_thermal_data {int nr_sensors; TYPE_1__* sensor; int /*<<< orphan*/  clk; struct platform_device* pdev; } ;
struct TYPE_2__ {char* irq_name; struct hisi_thermal_data* data; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HI6220_CLUSTER0_SENSOR ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 TYPE_1__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi6220_thermal_probe(struct hisi_thermal_data *data)
{
	struct platform_device *pdev = data->pdev;
	struct device *dev = &pdev->dev;
	int ret;

	data->clk = devm_clk_get(dev, "thermal_clk");
	if (IS_ERR(data->clk)) {
		ret = PTR_ERR(data->clk);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get thermal clk: %d\n", ret);
		return ret;
	}

	data->sensor = devm_kzalloc(dev, sizeof(*data->sensor), GFP_KERNEL);
	if (!data->sensor)
		return -ENOMEM;

	data->sensor[0].id = HI6220_CLUSTER0_SENSOR;
	data->sensor[0].irq_name = "tsensor_intr";
	data->sensor[0].data = data;
	data->nr_sensors = 1;

	return 0;
}