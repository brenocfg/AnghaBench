#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {TYPE_1__* chip; struct irq_data* parent_data; } ;
struct cpumask {int dummy; } ;
struct TYPE_2__ {int (* irq_set_affinity ) (struct irq_data*,struct cpumask const*,int) ;} ;

/* Variables and functions */
 int stub1 (struct irq_data*,struct cpumask const*,int) ; 

__attribute__((used)) static int hv_set_affinity(struct irq_data *data, const struct cpumask *dest,
			   bool force)
{
	struct irq_data *parent = data->parent_data;

	return parent->chip->irq_set_affinity(parent, dest, force);
}