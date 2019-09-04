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
typedef  unsigned int u64 ;

/* Variables and functions */

__attribute__((used)) static u64 vli_lshift(u64 *result, const u64 *in, unsigned int shift,
		      unsigned int ndigits)
{
	u64 carry = 0;
	int i;

	for (i = 0; i < ndigits; i++) {
		u64 temp = in[i];

		result[i] = (temp << shift) | carry;
		carry = temp >> (64 - shift);
	}

	return carry;
}