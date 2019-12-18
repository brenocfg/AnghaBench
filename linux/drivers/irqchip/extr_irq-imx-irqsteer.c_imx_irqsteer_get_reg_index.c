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
struct irqsteer_data {unsigned long reg_num; } ;

/* Variables and functions */

__attribute__((used)) static int imx_irqsteer_get_reg_index(struct irqsteer_data *data,
				      unsigned long irqnum)
{
	return (data->reg_num - irqnum / 32 - 1);
}