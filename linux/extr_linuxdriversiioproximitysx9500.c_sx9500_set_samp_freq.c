#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sx9500_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int val; int val2; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SX9500_REG_PROX_CTRL0 ; 
 int /*<<< orphan*/  SX9500_SCAN_PERIOD_MASK ; 
 int SX9500_SCAN_PERIOD_SHIFT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sx9500_samp_freq_table ; 

__attribute__((used)) static int sx9500_set_samp_freq(struct sx9500_data *data,
				int val, int val2)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sx9500_samp_freq_table); i++)
		if (val == sx9500_samp_freq_table[i].val &&
		    val2 == sx9500_samp_freq_table[i].val2)
			break;

	if (i == ARRAY_SIZE(sx9500_samp_freq_table))
		return -EINVAL;

	mutex_lock(&data->mutex);

	ret = regmap_update_bits(data->regmap, SX9500_REG_PROX_CTRL0,
				 SX9500_SCAN_PERIOD_MASK,
				 i << SX9500_SCAN_PERIOD_SHIFT);

	mutex_unlock(&data->mutex);

	return ret;
}