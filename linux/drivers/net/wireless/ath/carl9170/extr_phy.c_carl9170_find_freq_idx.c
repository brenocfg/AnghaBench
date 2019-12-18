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
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static int carl9170_find_freq_idx(int nfreqs, u8 *freqs, u8 f)
{
	int idx = nfreqs - 2;

	while (idx >= 0) {
		if (f >= freqs[idx])
			return idx;
		idx--;
	}

	return 0;
}