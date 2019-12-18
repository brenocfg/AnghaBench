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
struct power_supply_desc {int dummy; } ;
struct power_supply_config {int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; } ;
struct power_supply {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  notifier_call; } ;
struct nvec_power {TYPE_2__ notifier; int /*<<< orphan*/  poller; struct nvec_chip* nvec; } ;
struct nvec_chip {int dummy; } ;

/* Variables and functions */
#define  AC 129 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  BAT 128 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVEC_SYS ; 
 int PTR_ERR_OR_ZERO (struct power_supply*) ; 
 struct nvec_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct nvec_power*) ; 
 struct nvec_power* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bat_mfg_data (struct nvec_power*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct power_supply* nvec_bat_psy ; 
 struct power_supply_desc nvec_bat_psy_desc ; 
 int /*<<< orphan*/  nvec_power_bat_notifier ; 
 int /*<<< orphan*/  nvec_power_notifier ; 
 int /*<<< orphan*/  nvec_power_poll ; 
 int /*<<< orphan*/  nvec_power_supplied_to ; 
 struct power_supply* nvec_psy ; 
 struct power_supply_desc nvec_psy_desc ; 
 int /*<<< orphan*/  nvec_register_notifier (struct nvec_chip*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct power_supply* power_supply_register (TYPE_1__*,struct power_supply_desc const*,struct power_supply_config*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvec_power_probe(struct platform_device *pdev)
{
	struct power_supply **psy;
	const struct power_supply_desc *psy_desc;
	struct nvec_power *power;
	struct nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
	struct power_supply_config psy_cfg = {};

	power = devm_kzalloc(&pdev->dev, sizeof(struct nvec_power), GFP_NOWAIT);
	if (!power)
		return -ENOMEM;

	dev_set_drvdata(&pdev->dev, power);
	power->nvec = nvec;

	switch (pdev->id) {
	case AC:
		psy = &nvec_psy;
		psy_desc = &nvec_psy_desc;
		psy_cfg.supplied_to = nvec_power_supplied_to;
		psy_cfg.num_supplicants = ARRAY_SIZE(nvec_power_supplied_to);

		power->notifier.notifier_call = nvec_power_notifier;

		INIT_DELAYED_WORK(&power->poller, nvec_power_poll);
		schedule_delayed_work(&power->poller, msecs_to_jiffies(5000));
		break;
	case BAT:
		psy = &nvec_bat_psy;
		psy_desc = &nvec_bat_psy_desc;

		power->notifier.notifier_call = nvec_power_bat_notifier;
		break;
	default:
		return -ENODEV;
	}

	nvec_register_notifier(nvec, &power->notifier, NVEC_SYS);

	if (pdev->id == BAT)
		get_bat_mfg_data(power);

	*psy = power_supply_register(&pdev->dev, psy_desc, &psy_cfg);

	return PTR_ERR_OR_ZERO(*psy);
}