#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct gadc_thermal_info {int /*<<< orphan*/  tz_dev; int /*<<< orphan*/  channel; TYPE_1__* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  devm_iio_channel_get (TYPE_1__*,char*) ; 
 struct gadc_thermal_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_thermal_zone_of_sensor_register (TYPE_1__*,int /*<<< orphan*/ ,struct gadc_thermal_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gadc_thermal_ops ; 
 int gadc_thermal_read_linear_lookup_table (TYPE_1__*,struct gadc_thermal_info*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gadc_thermal_info*) ; 

__attribute__((used)) static int gadc_thermal_probe(struct platform_device *pdev)
{
	struct gadc_thermal_info *gti;
	int ret;

	if (!pdev->dev.of_node) {
		dev_err(&pdev->dev, "Only DT based supported\n");
		return -ENODEV;
	}

	gti = devm_kzalloc(&pdev->dev, sizeof(*gti), GFP_KERNEL);
	if (!gti)
		return -ENOMEM;

	ret = gadc_thermal_read_linear_lookup_table(&pdev->dev, gti);
	if (ret < 0)
		return ret;

	gti->dev = &pdev->dev;
	platform_set_drvdata(pdev, gti);

	gti->channel = devm_iio_channel_get(&pdev->dev, "sensor-channel");
	if (IS_ERR(gti->channel)) {
		ret = PTR_ERR(gti->channel);
		dev_err(&pdev->dev, "IIO channel not found: %d\n", ret);
		return ret;
	}

	gti->tz_dev = devm_thermal_zone_of_sensor_register(&pdev->dev, 0, gti,
							   &gadc_thermal_ops);
	if (IS_ERR(gti->tz_dev)) {
		ret = PTR_ERR(gti->tz_dev);
		dev_err(&pdev->dev, "Thermal zone sensor register failed: %d\n",
			ret);
		return ret;
	}

	return 0;
}