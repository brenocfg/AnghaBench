#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int of_regulator_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * stpmic1_matches ; 
 int /*<<< orphan*/ * stpmic1_regulator_cfgs ; 
 int stpmic1_regulator_register (struct platform_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stpmic1_regulator_probe(struct platform_device *pdev)
{
	int i, ret;

	ret = of_regulator_match(&pdev->dev, pdev->dev.of_node, stpmic1_matches,
				 ARRAY_SIZE(stpmic1_matches));
	if (ret < 0) {
		dev_err(&pdev->dev,
			"Error in PMIC regulator device tree node");
		return ret;
	}

	for (i = 0; i < ARRAY_SIZE(stpmic1_regulator_cfgs); i++) {
		ret = stpmic1_regulator_register(pdev, i, &stpmic1_matches[i],
						 &stpmic1_regulator_cfgs[i]);
		if (ret < 0)
			return ret;
	}

	dev_dbg(&pdev->dev, "stpmic1_regulator driver probed\n");

	return 0;
}