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
struct regmap_irq_chip_data {int irq_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

int regmap_irq_chip_get_base(struct regmap_irq_chip_data *data)
{
	WARN_ON(!data->irq_base);
	return data->irq_base;
}