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
struct TYPE_3__ {int odr; int bw_bits; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* bmg160_samp_freq_table ; 

__attribute__((used)) static int bmg160_convert_freq_to_bit(int val)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(bmg160_samp_freq_table); ++i) {
		if (bmg160_samp_freq_table[i].odr == val)
			return bmg160_samp_freq_table[i].bw_bits;
	}

	return -EINVAL;
}