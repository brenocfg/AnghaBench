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
typedef  int u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int DIV_ROUND_UP_ULL (int,int /*<<< orphan*/ ) ; 
 int U32_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline u32 div_round_up_u32_fixed16(u32 val, uint_fixed_16_16_t d)
{
	u64 tmp;

	tmp = (u64)val << 16;
	tmp = DIV_ROUND_UP_ULL(tmp, d.val);
	WARN_ON(tmp > U32_MAX);

	return (u32)tmp;
}