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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline long IN_FROM_REG(u8 val, int in_num)
{
	/*
	 * To avoid floating point, we multiply constants by 10 (100 for +12V).
	 * We also multiply them by 1000 because we want 0.001V/bit for the
	 * output value. Rounding is done.
	 */
	if (in_num <= 1)
		return (long) ((250000 * val + 1330000 + 21024 / 2) / 21024);
	else if (in_num == 2)
		return (long) ((250000 * val + 1330000 + 15737 / 2) / 15737);
	else if (in_num == 3)
		return (long) ((250000 * val + 1330000 + 10108 / 2) / 10108);
	else
		return (long) ((2500000 * val + 13300000 + 41714 / 2) / 41714);
}