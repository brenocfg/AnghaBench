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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  OCOTP_ANA1 ; 
 int /*<<< orphan*/  OCOTP_MEM0 ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int imx_init_calib (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_init_temp_grade (struct platform_device*,int /*<<< orphan*/ ) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int imx_init_from_tempmon_data(struct platform_device *pdev)
{
	struct regmap *map;
	int ret;
	u32 val;

	map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
					      "fsl,tempmon-data");
	if (IS_ERR(map)) {
		ret = PTR_ERR(map);
		dev_err(&pdev->dev, "failed to get sensor regmap: %d\n", ret);
		return ret;
	}

	ret = regmap_read(map, OCOTP_ANA1, &val);
	if (ret) {
		dev_err(&pdev->dev, "failed to read sensor data: %d\n", ret);
		return ret;
	}
	ret = imx_init_calib(pdev, val);
	if (ret)
		return ret;

	ret = regmap_read(map, OCOTP_MEM0, &val);
	if (ret) {
		dev_err(&pdev->dev, "failed to read sensor data: %d\n", ret);
		return ret;
	}
	imx_init_temp_grade(pdev, val);

	return 0;
}