#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * timings; int /*<<< orphan*/ * funcs; int /*<<< orphan*/  of_node; struct thc63_dev* driver_private; } ;
struct thc63_dev {TYPE_1__ bridge; int /*<<< orphan*/  timings; int /*<<< orphan*/  vcc; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct thc63_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get_optional (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct thc63_dev*) ; 
 int /*<<< orphan*/  thc63_bridge_func ; 
 int thc63_gpio_init (struct thc63_dev*) ; 
 int thc63_parse_dt (struct thc63_dev*) ; 

__attribute__((used)) static int thc63_probe(struct platform_device *pdev)
{
	struct thc63_dev *thc63;
	int ret;

	thc63 = devm_kzalloc(&pdev->dev, sizeof(*thc63), GFP_KERNEL);
	if (!thc63)
		return -ENOMEM;

	thc63->dev = &pdev->dev;
	platform_set_drvdata(pdev, thc63);

	thc63->vcc = devm_regulator_get_optional(thc63->dev, "vcc");
	if (IS_ERR(thc63->vcc)) {
		if (PTR_ERR(thc63->vcc) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_err(thc63->dev, "Unable to get \"vcc\" supply: %ld\n",
			PTR_ERR(thc63->vcc));
		return PTR_ERR(thc63->vcc);
	}

	ret = thc63_gpio_init(thc63);
	if (ret)
		return ret;

	ret = thc63_parse_dt(thc63);
	if (ret)
		return ret;

	thc63->bridge.driver_private = thc63;
	thc63->bridge.of_node = pdev->dev.of_node;
	thc63->bridge.funcs = &thc63_bridge_func;
	thc63->bridge.timings = &thc63->timings;

	drm_bridge_add(&thc63->bridge);

	return 0;
}