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
struct tps65912 {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps65912_cells ; 
 int /*<<< orphan*/  tps65912_irq_chip ; 

int tps65912_device_init(struct tps65912 *tps)
{
	int ret;

	ret = regmap_add_irq_chip(tps->regmap, tps->irq, IRQF_ONESHOT, 0,
				  &tps65912_irq_chip, &tps->irq_data);
	if (ret)
		return ret;

	ret = mfd_add_devices(tps->dev, PLATFORM_DEVID_AUTO, tps65912_cells,
			      ARRAY_SIZE(tps65912_cells), NULL, 0,
			      regmap_irq_get_domain(tps->irq_data));
	if (ret) {
		regmap_del_irq_chip(tps->irq, tps->irq_data);
		return ret;
	}

	return 0;
}