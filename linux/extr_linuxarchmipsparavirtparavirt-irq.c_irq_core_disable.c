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
struct irq_data {int dummy; } ;
struct core_chip_data {int desired_en; } ;

/* Variables and functions */
 struct core_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void irq_core_disable(struct irq_data *data)
{
	struct core_chip_data *cd = irq_data_get_irq_chip_data(data);
	cd->desired_en = false;
}