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
struct ltr501_samp_table {int freq_val; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ltr501_match_samp_freq(const struct ltr501_samp_table *tab,
					   int len, int val, int val2)
{
	int i, freq;

	freq = val * 1000000 + val2;

	for (i = 0; i < len; i++) {
		if (tab[i].freq_val == freq)
			return i;
	}

	return -EINVAL;
}