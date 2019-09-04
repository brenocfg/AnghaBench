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
 int mma8452_change_config (struct mma8452_data*,int /*<<< orphan*/ ,int) ; 
 int mma8452_get_hp_filter_index (struct mma8452_data*,int,int) ; 

__attribute__((used)) static int mma8452_set_hp_filter_frequency(struct mma8452_data *data,
					   int val, int val2)
{
	int i, reg;

	i = mma8452_get_hp_filter_index(data, val, val2);
	if (i < 0)
		return i;

	reg = i2c_smbus_read_byte_data(data->client,
				       MMA8452_HP_FILTER_CUTOFF);
	if (reg < 0)
		return reg;

	reg &= ~MMA8452_HP_FILTER_CUTOFF_SEL_MASK;
	reg |= i;

	return mma8452_change_config(data, MMA8452_HP_FILTER_CUTOFF, reg);
}