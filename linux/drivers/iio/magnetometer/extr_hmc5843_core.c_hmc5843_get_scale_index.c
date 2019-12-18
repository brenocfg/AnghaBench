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
struct hmc5843_data {TYPE_1__* variant; } ;
struct TYPE_2__ {int n_regval_to_nanoscale; int* regval_to_nanoscale; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int hmc5843_get_scale_index(struct hmc5843_data *data, int val, int val2)
{
	int i;

	if (val)
		return -EINVAL;

	for (i = 0; i < data->variant->n_regval_to_nanoscale; i++)
		if (val2 == data->variant->regval_to_nanoscale[i])
			return i;

	return -EINVAL;
}