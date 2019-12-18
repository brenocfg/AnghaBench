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
struct regmap_irq_chip_data {int dummy; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int cpcap_sense_irq (struct regmap*,int) ; 
 struct regmap_irq_chip_data* irq_get_chip_data (int) ; 
 int regmap_irq_chip_get_base (struct regmap_irq_chip_data*) ; 

int cpcap_sense_virq(struct regmap *regmap, int virq)
{
	struct regmap_irq_chip_data *d = irq_get_chip_data(virq);
	int irq_base = regmap_irq_chip_get_base(d);

	return cpcap_sense_irq(regmap, virq - irq_base);
}