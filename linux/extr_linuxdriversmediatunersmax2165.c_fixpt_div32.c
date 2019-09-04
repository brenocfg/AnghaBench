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
 int EINVAL ; 

__attribute__((used)) static int fixpt_div32(u32 dividend, u32 divisor, u32 *quotient, u32 *fraction)
{
	u32 remainder;
	u32 q, f = 0;
	int i;

	if (0 == divisor)
		return -EINVAL;

	q = dividend / divisor;
	remainder = dividend - q * divisor;

	for (i = 0; i < 31; i++) {
		remainder <<= 1;
		if (remainder >= divisor) {
			f += 1;
			remainder -= divisor;
		}
		f <<= 1;
	}

	*quotient = q;
	*fraction = f;

	return 0;
}