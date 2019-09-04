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
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ uint_fixed_16_16_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int DIV_ROUND_UP_ULL (int,int /*<<< orphan*/ ) ; 
 int U32_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline uint32_t div_round_up_u32_fixed16(uint32_t val,
						uint_fixed_16_16_t d)
{
	uint64_t interm_val;

	interm_val = (uint64_t)val << 16;
	interm_val = DIV_ROUND_UP_ULL(interm_val, d.val);
	WARN_ON(interm_val > U32_MAX);
	return (uint32_t) interm_val;
}