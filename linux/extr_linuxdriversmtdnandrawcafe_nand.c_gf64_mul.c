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

__attribute__((used)) static unsigned short gf64_mul(u8 a, u8 b)
{
	u8 c;
	unsigned int i;

	c = 0;
	for (i = 0; i < 6; i++) {
		if (a & 1)
			c ^= b;
		a >>= 1;
		b <<= 1;
		if ((b & 0x40) != 0)
			b ^= 0x43;
	}

	return c;
}