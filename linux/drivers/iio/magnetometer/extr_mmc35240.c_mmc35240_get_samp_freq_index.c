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
struct mmc35240_data {int dummy; } ;
struct TYPE_3__ {int val; int val2; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* mmc35240_samp_freq ; 

__attribute__((used)) static int mmc35240_get_samp_freq_index(struct mmc35240_data *data,
					int val, int val2)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mmc35240_samp_freq); i++)
		if (mmc35240_samp_freq[i].val == val &&
		    mmc35240_samp_freq[i].val2 == val2)
			return i;
	return -EINVAL;
}