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
struct sx9500_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int val; int val2; } ;

/* Variables and functions */
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  SX9500_REG_PROX_CTRL0 ; 
 unsigned int SX9500_SCAN_PERIOD_MASK ; 
 unsigned int SX9500_SCAN_PERIOD_SHIFT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 TYPE_1__* sx9500_samp_freq_table ; 

__attribute__((used)) static int sx9500_read_samp_freq(struct sx9500_data *data,
				 int *val, int *val2)
{
	int ret;
	unsigned int regval;

	mutex_lock(&data->mutex);
	ret = regmap_read(data->regmap, SX9500_REG_PROX_CTRL0, &regval);
	mutex_unlock(&data->mutex);

	if (ret < 0)
		return ret;

	regval = (regval & SX9500_SCAN_PERIOD_MASK) >> SX9500_SCAN_PERIOD_SHIFT;
	*val = sx9500_samp_freq_table[regval].val;
	*val2 = sx9500_samp_freq_table[regval].val2;

	return IIO_VAL_INT_PLUS_MICRO;
}