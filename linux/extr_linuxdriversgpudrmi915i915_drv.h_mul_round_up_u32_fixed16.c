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
struct TYPE_3__ {int val; } ;
typedef  TYPE_1__ uint_fixed_16_16_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int DIV_ROUND_UP_ULL (int,int) ; 
 int U32_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline uint32_t mul_round_up_u32_fixed16(uint32_t val,
						uint_fixed_16_16_t mul)
{
	uint64_t intermediate_val;

	intermediate_val = (uint64_t) val * mul.val;
	intermediate_val = DIV_ROUND_UP_ULL(intermediate_val, 1 << 16);
	WARN_ON(intermediate_val > U32_MAX);
	return (uint32_t) intermediate_val;
}