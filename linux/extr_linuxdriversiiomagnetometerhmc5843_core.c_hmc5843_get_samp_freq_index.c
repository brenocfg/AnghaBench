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
struct TYPE_2__ {int n_regval_to_samp_freq; int** regval_to_samp_freq; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int hmc5843_get_samp_freq_index(struct hmc5843_data *data,
				       int val, int val2)
{
	int i;

	for (i = 0; i < data->variant->n_regval_to_samp_freq; i++)
		if (val == data->variant->regval_to_samp_freq[i][0] &&
		    val2 == data->variant->regval_to_samp_freq[i][1])
			return i;

	return -EINVAL;
}