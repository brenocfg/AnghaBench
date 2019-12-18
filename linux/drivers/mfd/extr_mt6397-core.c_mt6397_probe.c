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
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mt6397_chip {unsigned int chip_id; scalar_t__ irq; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  regmap; TYPE_1__* dev; } ;
struct chip_data {unsigned int cid_shift; int /*<<< orphan*/  cid_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  MT6323_CHIP_ID 130 
#define  MT6391_CHIP_ID 129 
#define  MT6397_CHIP_ID 128 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mt6397_chip* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt6323_devs ; 
 int /*<<< orphan*/  mt6397_devs ; 
 int mt6397_irq_init (struct mt6397_chip*) ; 
 struct chip_data* of_device_get_match_data (TYPE_1__*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mt6397_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mt6397_probe(struct platform_device *pdev)
{
	int ret;
	unsigned int id;
	struct mt6397_chip *pmic;
	const struct chip_data *pmic_core;

	pmic = devm_kzalloc(&pdev->dev, sizeof(*pmic), GFP_KERNEL);
	if (!pmic)
		return -ENOMEM;

	pmic->dev = &pdev->dev;

	/*
	 * mt6397 MFD is child device of soc pmic wrapper.
	 * Regmap is set from its parent.
	 */
	pmic->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!pmic->regmap)
		return -ENODEV;

	pmic_core = of_device_get_match_data(&pdev->dev);
	if (!pmic_core)
		return -ENODEV;

	ret = regmap_read(pmic->regmap, pmic_core->cid_addr, &id);
	if (ret) {
		dev_err(&pdev->dev, "Failed to read chip id: %d\n", ret);
		return ret;
	}

	pmic->chip_id = (id >> pmic_core->cid_shift) & 0xff;

	platform_set_drvdata(pdev, pmic);

	pmic->irq = platform_get_irq(pdev, 0);
	if (pmic->irq <= 0)
		return pmic->irq;

	ret = mt6397_irq_init(pmic);
	if (ret)
		return ret;

	switch (pmic->chip_id) {
	case MT6323_CHIP_ID:
		ret = devm_mfd_add_devices(&pdev->dev, -1, mt6323_devs,
					   ARRAY_SIZE(mt6323_devs), NULL,
					   0, pmic->irq_domain);
		break;

	case MT6391_CHIP_ID:
	case MT6397_CHIP_ID:
		ret = devm_mfd_add_devices(&pdev->dev, -1, mt6397_devs,
					   ARRAY_SIZE(mt6397_devs), NULL,
					   0, pmic->irq_domain);
		break;

	default:
		dev_err(&pdev->dev, "unsupported chip: %d\n", pmic->chip_id);
		return -ENODEV;
	}

	if (ret) {
		irq_domain_remove(pmic->irq_domain);
		dev_err(&pdev->dev, "failed to add child devices: %d\n", ret);
	}

	return ret;
}