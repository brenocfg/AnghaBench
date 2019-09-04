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
typedef  int /*<<< orphan*/  uint_fixed_16_16_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int DIV_ROUND_UP_ULL (int,scalar_t__) ; 
 int /*<<< orphan*/  clamp_u64_to_fixed16 (int) ; 

__attribute__((used)) static inline uint_fixed_16_16_t div_fixed16(uint32_t val, uint32_t d)
{
	uint64_t interm_val;

	interm_val = (uint64_t)val << 16;
	interm_val = DIV_ROUND_UP_ULL(interm_val, d);
	return clamp_u64_to_fixed16(interm_val);
}