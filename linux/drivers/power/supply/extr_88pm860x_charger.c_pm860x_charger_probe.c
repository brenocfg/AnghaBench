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
struct power_supply_config {scalar_t__* supplied_to; int num_supplicants; struct pm860x_charger_info* drv_data; } ;
struct pm860x_chip {scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  client; int /*<<< orphan*/  companion; } ;
struct pm860x_charger_info {scalar_t__* irq; int irq_nums; int /*<<< orphan*/  usb; int /*<<< orphan*/  lock; TYPE_1__* dev; int /*<<< orphan*/  i2c_8606; int /*<<< orphan*/  i2c; struct pm860x_chip* chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int num_resources; TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ CHIP_PM8607 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHG_NORMAL_LOW ; 
 int /*<<< orphan*/  VCHG_OVP_LOW ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct pm860x_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct pm860x_charger_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct pm860x_charger_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pm860x_charger_info*) ; 
 int /*<<< orphan*/  pm860x_charger_desc ; 
 int /*<<< orphan*/  pm860x_init_charger (struct pm860x_charger_info*) ; 
 TYPE_2__* pm860x_irq_descs ; 
 scalar_t__* pm860x_supplied_to ; 
 int /*<<< orphan*/  power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pm860x_charger_info*) ; 
 int /*<<< orphan*/  set_vchg_threshold (struct pm860x_charger_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm860x_charger_probe(struct platform_device *pdev)
{
	struct pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct power_supply_config psy_cfg = {};
	struct pm860x_charger_info *info;
	int ret;
	int count;
	int i;
	int j;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	count = pdev->num_resources;
	for (i = 0, j = 0; i < count; i++) {
		info->irq[j] = platform_get_irq(pdev, i);
		if (info->irq[j] < 0)
			continue;
		j++;
	}
	info->irq_nums = j;

	info->chip = chip;
	info->i2c =
	    (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	info->i2c_8606 =
	    (chip->id == CHIP_PM8607) ? chip->companion : chip->client;
	if (!info->i2c_8606) {
		dev_err(&pdev->dev, "Missed I2C address of 88PM8606!\n");
		ret = -EINVAL;
		goto out;
	}
	info->dev = &pdev->dev;

	/* set init value for the case we are not using battery */
	set_vchg_threshold(info, VCHG_NORMAL_LOW, VCHG_OVP_LOW);

	mutex_init(&info->lock);
	platform_set_drvdata(pdev, info);

	psy_cfg.drv_data = info;
	psy_cfg.supplied_to = pm860x_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(pm860x_supplied_to);
	info->usb = power_supply_register(&pdev->dev, &pm860x_charger_desc,
					  &psy_cfg);
	if (IS_ERR(info->usb)) {
		ret = PTR_ERR(info->usb);
		goto out;
	}

	pm860x_init_charger(info);

	for (i = 0; i < ARRAY_SIZE(info->irq); i++) {
		ret = request_threaded_irq(info->irq[i], NULL,
			pm860x_irq_descs[i].handler,
			IRQF_ONESHOT, pm860x_irq_descs[i].name, info);
		if (ret < 0) {
			dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
				info->irq[i], ret);
			goto out_irq;
		}
	}
	return 0;

out_irq:
	power_supply_unregister(info->usb);
	while (--i >= 0)
		free_irq(info->irq[i], info);
out:
	return ret;
}