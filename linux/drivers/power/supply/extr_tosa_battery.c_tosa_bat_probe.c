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
struct power_supply_config {TYPE_1__* drv_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {void* psy; int /*<<< orphan*/  work_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  TOSA_GPIO_BAT0_CRG ; 
 int /*<<< orphan*/  TOSA_GPIO_BAT1_CRG ; 
 int /*<<< orphan*/  TOSA_GPIO_JACKET_DETECT ; 
 int /*<<< orphan*/  bat_work ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_request_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_is_tosa () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* power_supply_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  power_supply_unregister (void*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 TYPE_1__ tosa_bat_bu ; 
 int /*<<< orphan*/  tosa_bat_bu_desc ; 
 int /*<<< orphan*/  tosa_bat_gpio_isr ; 
 int /*<<< orphan*/  tosa_bat_gpios ; 
 TYPE_1__ tosa_bat_jacket ; 
 int /*<<< orphan*/  tosa_bat_jacket_desc ; 
 TYPE_1__ tosa_bat_main ; 
 int /*<<< orphan*/  tosa_bat_main_desc ; 
 int /*<<< orphan*/  tosa_bat_work ; 

__attribute__((used)) static int tosa_bat_probe(struct platform_device *dev)
{
	int ret;
	struct power_supply_config main_psy_cfg = {},
				   jacket_psy_cfg = {},
				   bu_psy_cfg = {};

	if (!machine_is_tosa())
		return -ENODEV;

	ret = gpio_request_array(tosa_bat_gpios, ARRAY_SIZE(tosa_bat_gpios));
	if (ret)
		return ret;

	mutex_init(&tosa_bat_main.work_lock);
	mutex_init(&tosa_bat_jacket.work_lock);

	INIT_WORK(&bat_work, tosa_bat_work);

	main_psy_cfg.drv_data = &tosa_bat_main;
	tosa_bat_main.psy = power_supply_register(&dev->dev,
						  &tosa_bat_main_desc,
						  &main_psy_cfg);
	if (IS_ERR(tosa_bat_main.psy)) {
		ret = PTR_ERR(tosa_bat_main.psy);
		goto err_psy_reg_main;
	}

	jacket_psy_cfg.drv_data = &tosa_bat_jacket;
	tosa_bat_jacket.psy = power_supply_register(&dev->dev,
						    &tosa_bat_jacket_desc,
						    &jacket_psy_cfg);
	if (IS_ERR(tosa_bat_jacket.psy)) {
		ret = PTR_ERR(tosa_bat_jacket.psy);
		goto err_psy_reg_jacket;
	}

	bu_psy_cfg.drv_data = &tosa_bat_bu;
	tosa_bat_bu.psy = power_supply_register(&dev->dev, &tosa_bat_bu_desc,
						&bu_psy_cfg);
	if (IS_ERR(tosa_bat_bu.psy)) {
		ret = PTR_ERR(tosa_bat_bu.psy);
		goto err_psy_reg_bu;
	}

	ret = request_irq(gpio_to_irq(TOSA_GPIO_BAT0_CRG),
				tosa_bat_gpio_isr,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"main full", &tosa_bat_main);
	if (ret)
		goto err_req_main;

	ret = request_irq(gpio_to_irq(TOSA_GPIO_BAT1_CRG),
				tosa_bat_gpio_isr,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"jacket full", &tosa_bat_jacket);
	if (ret)
		goto err_req_jacket;

	ret = request_irq(gpio_to_irq(TOSA_GPIO_JACKET_DETECT),
				tosa_bat_gpio_isr,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"jacket detect", &tosa_bat_jacket);
	if (!ret) {
		schedule_work(&bat_work);
		return 0;
	}

	free_irq(gpio_to_irq(TOSA_GPIO_BAT1_CRG), &tosa_bat_jacket);
err_req_jacket:
	free_irq(gpio_to_irq(TOSA_GPIO_BAT0_CRG), &tosa_bat_main);
err_req_main:
	power_supply_unregister(tosa_bat_bu.psy);
err_psy_reg_bu:
	power_supply_unregister(tosa_bat_jacket.psy);
err_psy_reg_jacket:
	power_supply_unregister(tosa_bat_main.psy);
err_psy_reg_main:

	/* see comment in tosa_bat_remove */
	cancel_work_sync(&bat_work);

	gpio_free_array(tosa_bat_gpios, ARRAY_SIZE(tosa_bat_gpios));
	return ret;
}