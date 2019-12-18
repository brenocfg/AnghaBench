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
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ uint_fixed_16_16_t ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 TYPE_1__ clamp_u64_to_fixed16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_u32_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint_fixed_16_16_t mul_u32_fixed16(u32 val, uint_fixed_16_16_t mul)
{
	u64 tmp;

	tmp = mul_u32_u32(val, mul.val);

	return clamp_u64_to_fixed16(tmp);
}