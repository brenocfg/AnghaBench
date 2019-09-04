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

__attribute__((used)) static bool vli_is_zero(const u64 *vli, unsigned int ndigits)
{
	int i;

	for (i = 0; i < ndigits; i++) {
		if (vli[i])
			return false;
	}

	return true;
}