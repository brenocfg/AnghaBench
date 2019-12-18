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
typedef  scalar_t__ u32 ;
struct irqsteer_data {int irq_count; scalar_t__* irq; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int imx_irqsteer_get_hwirq_base(struct irqsteer_data *data, u32 irq)
{
	int i;

	for (i = 0; i < data->irq_count; i++) {
		if (data->irq[i] == irq)
			return i * 64;
	}

	return -EINVAL;
}