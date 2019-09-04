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
typedef  scalar_t__ u64 ;

/* Variables and functions */

__attribute__((used)) static int vli_cmp(const u64 *left, const u64 *right, unsigned int ndigits)
{
	int i;

	for (i = ndigits - 1; i >= 0; i--) {
		if (left[i] > right[i])
			return 1;
		else if (left[i] < right[i])
			return -1;
	}

	return 0;
}