#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int m_low; int m_high; } ;
typedef  TYPE_1__ uint128_t ;
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static uint128_t mul_64_64(u64 left, u64 right)
{
	u64 a0 = left & 0xffffffffull;
	u64 a1 = left >> 32;
	u64 b0 = right & 0xffffffffull;
	u64 b1 = right >> 32;
	u64 m0 = a0 * b0;
	u64 m1 = a0 * b1;
	u64 m2 = a1 * b0;
	u64 m3 = a1 * b1;
	uint128_t result;

	m2 += (m0 >> 32);
	m2 += m1;

	/* Overflow */
	if (m2 < m1)
		m3 += 0x100000000ull;

	result.m_low = (m0 & 0xffffffffull) | (m2 << 32);
	result.m_high = m3 + (m2 >> 32);

	return result;
}