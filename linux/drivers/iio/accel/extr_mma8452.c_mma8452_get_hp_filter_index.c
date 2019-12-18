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
struct mma8452_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int mma8452_get_int_plus_micros_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int mma8452_get_odr_index (struct mma8452_data*) ; 
 int mma8452_get_power_mode (struct mma8452_data*) ; 
 int /*<<< orphan*/ ** mma8452_hp_filter_cutoff ; 

__attribute__((used)) static int mma8452_get_hp_filter_index(struct mma8452_data *data,
				       int val, int val2)
{
	int i, j;

	i = mma8452_get_odr_index(data);
	j = mma8452_get_power_mode(data);
	if (j < 0)
		return j;

	return mma8452_get_int_plus_micros_index(mma8452_hp_filter_cutoff[j][i],
		ARRAY_SIZE(mma8452_hp_filter_cutoff[0][0]), val, val2);
}