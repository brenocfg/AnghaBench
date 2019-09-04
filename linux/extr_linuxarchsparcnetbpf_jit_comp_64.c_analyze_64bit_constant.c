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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void analyze_64bit_constant(u32 high_bits, u32 low_bits,
				   int *hbsp, int *lbsp, int *abbasp)
{
	int lowest_bit_set, highest_bit_set, all_bits_between_are_set;
	int i;

	lowest_bit_set = highest_bit_set = -1;
	i = 0;
	do {
		if ((lowest_bit_set == -1) && ((low_bits >> i) & 1))
			lowest_bit_set = i;
		if ((highest_bit_set == -1) && ((high_bits >> (32 - i - 1)) & 1))
			highest_bit_set = (64 - i - 1);
	}  while (++i < 32 && (highest_bit_set == -1 ||
			       lowest_bit_set == -1));
	if (i == 32) {
		i = 0;
		do {
			if (lowest_bit_set == -1 && ((high_bits >> i) & 1))
				lowest_bit_set = i + 32;
			if (highest_bit_set == -1 &&
			    ((low_bits >> (32 - i - 1)) & 1))
				highest_bit_set = 32 - i - 1;
		} while (++i < 32 && (highest_bit_set == -1 ||
				      lowest_bit_set == -1));
	}

	all_bits_between_are_set = 1;
	for (i = lowest_bit_set; i <= highest_bit_set; i++) {
		if (i < 32) {
			if ((low_bits & (1 << i)) != 0)
				continue;
		} else {
			if ((high_bits & (1 << (i - 32))) != 0)
				continue;
		}
		all_bits_between_are_set = 0;
		break;
	}
	*hbsp = highest_bit_set;
	*lbsp = lowest_bit_set;
	*abbasp = all_bits_between_are_set;
}