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
struct mma8452_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMA8452_HP_FILTER_CUTOFF ; 
 int MMA8452_HP_FILTER_CUTOFF_SEL_MASK ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mma8452_get_odr_index (struct mma8452_data*) ; 
 int mma8452_get_power_mode (struct mma8452_data*) ; 
 int**** mma8452_hp_filter_cutoff ; 

__attribute__((used)) static int mma8452_read_hp_filter(struct mma8452_data *data, int *hz, int *uHz)
{
	int j, i, ret;

	ret = i2c_smbus_read_byte_data(data->client, MMA8452_HP_FILTER_CUTOFF);
	if (ret < 0)
		return ret;

	i = mma8452_get_odr_index(data);
	j = mma8452_get_power_mode(data);
	if (j < 0)
		return j;

	ret &= MMA8452_HP_FILTER_CUTOFF_SEL_MASK;
	*hz = mma8452_hp_filter_cutoff[j][i][ret][0];
	*uHz = mma8452_hp_filter_cutoff[j][i][ret][1];

	return 0;
}