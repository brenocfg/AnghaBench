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

/* Variables and functions */

__attribute__((used)) static inline u64 reverse(u64 data, int bits)
{
	int i;
	u64 c;

	c = 0;
	for (i = 0; i < bits; i++) {
		c |= (u64) (((data & (((u64) 1) << i)) ? 1 : 0))
			<< (bits - 1 - i);
	}
	return (c);
}