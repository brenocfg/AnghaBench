#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct intel_soc_pmic {int /*<<< orphan*/  regmap; struct device* dev; } ;
struct TYPE_5__ {int start; int end; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* bcove_dev ; 
 int /*<<< orphan*/  bcove_regmap_config ; 
 struct intel_soc_pmic* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (struct device*,int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init (struct device*,int /*<<< orphan*/ *,struct intel_soc_pmic*,int /*<<< orphan*/ *) ; 
 TYPE_1__* irq_level2_resources ; 
 int platform_get_irq (struct platform_device*,unsigned int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct intel_soc_pmic*) ; 

__attribute__((used)) static int bcove_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct intel_soc_pmic *pmic;
	unsigned int i;
	int ret;

	pmic = devm_kzalloc(dev, sizeof(*pmic), GFP_KERNEL);
	if (!pmic)
		return -ENOMEM;

	platform_set_drvdata(pdev, pmic);
	pmic->dev = &pdev->dev;

	pmic->regmap = devm_regmap_init(dev, NULL, pmic, &bcove_regmap_config);
	if (IS_ERR(pmic->regmap))
		return PTR_ERR(pmic->regmap);

	for (i = 0; i < ARRAY_SIZE(irq_level2_resources); i++) {
		ret = platform_get_irq(pdev, i);
		if (ret < 0)
			return ret;

		irq_level2_resources[i].start = ret;
		irq_level2_resources[i].end = ret;
	}

	return devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				    bcove_dev, ARRAY_SIZE(bcove_dev),
				    NULL, 0, NULL);
}