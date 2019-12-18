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
 int mma8452_get_odr_index (struct mma8452_data*) ; 
 int** mma8452_samp_freq ; 

__attribute__((used)) static int mma8452_calculate_sleep(struct mma8452_data *data)
{
	int ret, i = mma8452_get_odr_index(data);

	if (mma8452_samp_freq[i][0] > 0)
		ret = 1000 / mma8452_samp_freq[i][0];
	else
		ret = 1000;

	return ret == 0 ? 1 : ret;
}