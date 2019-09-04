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
typedef  int uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t shrd128(uint64_t high, uint64_t low, uint8_t shift)
{
	low >>= shift;
	low  |= (high << 1) << (63U - shift);
	return low;
}