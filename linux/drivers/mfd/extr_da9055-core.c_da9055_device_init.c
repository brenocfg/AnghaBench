#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct da9055_pdata {int irq_base; int /*<<< orphan*/  (* init ) (struct da9055*) ;} ;
struct da9055 {int irq_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  chip_irq; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DA9055_REG_EVENT_A ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  da9055_devs ; 
 int da9055_group_write (struct da9055*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  da9055_regmap_irq_chip ; 
 struct da9055_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int regmap_irq_chip_get_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct da9055*) ; 

int da9055_device_init(struct da9055 *da9055)
{
	struct da9055_pdata *pdata = dev_get_platdata(da9055->dev);
	int ret;
	uint8_t clear_events[3] = {0xFF, 0xFF, 0xFF};

	if (pdata && pdata->init != NULL)
		pdata->init(da9055);

	if (!pdata || !pdata->irq_base)
		da9055->irq_base = -1;
	else
		da9055->irq_base = pdata->irq_base;

	ret = da9055_group_write(da9055, DA9055_REG_EVENT_A, 3, clear_events);
	if (ret < 0)
		return ret;

	ret = regmap_add_irq_chip(da9055->regmap, da9055->chip_irq,
				  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				  da9055->irq_base, &da9055_regmap_irq_chip,
				  &da9055->irq_data);
	if (ret < 0)
		return ret;

	da9055->irq_base = regmap_irq_chip_get_base(da9055->irq_data);

	ret = mfd_add_devices(da9055->dev, -1,
			      da9055_devs, ARRAY_SIZE(da9055_devs),
			      NULL, da9055->irq_base, NULL);
	if (ret)
		goto err;

	return 0;

err:
	mfd_remove_devices(da9055->dev);
	return ret;
}