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
struct TYPE_5__ {int val; } ;
typedef  TYPE_1__ uint_fixed_16_16_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 TYPE_1__ clamp_u64_to_fixed16 (int) ; 

__attribute__((used)) static inline uint_fixed_16_16_t mul_u32_fixed16(uint32_t val,
						     uint_fixed_16_16_t mul)
{
	uint64_t intermediate_val;

	intermediate_val = (uint64_t) val * mul.val;
	return clamp_u64_to_fixed16(intermediate_val);
}