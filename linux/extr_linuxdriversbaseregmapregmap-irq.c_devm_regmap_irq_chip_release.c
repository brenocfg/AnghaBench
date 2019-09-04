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
struct regmap_irq_chip_data {int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,struct regmap_irq_chip_data*) ; 

__attribute__((used)) static void devm_regmap_irq_chip_release(struct device *dev, void *res)
{
	struct regmap_irq_chip_data *d = *(struct regmap_irq_chip_data **)res;

	regmap_del_irq_chip(d->irq, d);
}