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

__attribute__((used)) static u32 word_sum_v2(u32 *p, u32 num)
{
	u32 sum = 0;
	int i;

	for (i = 0; i < num; i++) {
		u32 val;

		val = p[i];
		if (val > ~sum)
			sum++;
		sum += val;
	}
	return ~sum;
}