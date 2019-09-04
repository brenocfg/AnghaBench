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
typedef  int u64 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */

__attribute__((used)) static u64 advance_polynomial(u64 poly, u64 val, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		int highbit_set = ((s64)val < 0);

		val <<= 1;
		if (highbit_set)
			val ^= poly;
	}

	return val;
}