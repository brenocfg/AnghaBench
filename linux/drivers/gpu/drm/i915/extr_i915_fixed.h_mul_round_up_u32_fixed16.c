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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP_ULL (scalar_t__,int) ; 
 scalar_t__ U32_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ mul_u32_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 mul_round_up_u32_fixed16(u32 val, uint_fixed_16_16_t mul)
{
	u64 tmp;

	tmp = mul_u32_u32(val, mul.val);
	tmp = DIV_ROUND_UP_ULL(tmp, 1 << 16);
	WARN_ON(tmp > U32_MAX);

	return (u32)tmp;
}