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
 int SHORT_BITS ; 

__attribute__((used)) static u32 altera_bits_req(u32 n)
{
	u32 result = SHORT_BITS;

	if (n == 0)
		result = 1;
	else {
		/* Look for the highest non-zero bit position */
		while ((n & (1 << (SHORT_BITS - 1))) == 0) {
			n <<= 1;
			--result;
		}
	}

	return result;
}