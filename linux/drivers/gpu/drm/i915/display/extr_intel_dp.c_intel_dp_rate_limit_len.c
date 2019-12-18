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

/* Variables and functions */

__attribute__((used)) static int intel_dp_rate_limit_len(const int *rates, int len, int max_rate)
{
	int i;

	/* Limit results by potentially reduced max rate */
	for (i = 0; i < len; i++) {
		if (rates[len - i - 1] <= max_rate)
			return len - i;
	}

	return 0;
}