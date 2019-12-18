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
 scalar_t__ U32_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline uint_fixed_16_16_t clamp_u64_to_fixed16(u64 val)
{
	uint_fixed_16_16_t fp = { .val = (u32)val };

	WARN_ON(val > U32_MAX);

	return fp;
}