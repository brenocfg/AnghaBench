#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ m_low; scalar_t__ m_high; } ;
typedef  TYPE_1__ uint128_t ;

/* Variables and functions */

__attribute__((used)) static uint128_t add_128_128(uint128_t a, uint128_t b)
{
	uint128_t result;

	result.m_low = a.m_low + b.m_low;
	result.m_high = a.m_high + b.m_high + (result.m_low < a.m_low);

	return result;
}