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
struct TYPE_3__ {scalar_t__ val; } ;
typedef  TYPE_1__ uint_fixed_16_16_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ U32_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline uint_fixed_16_16_t clamp_u64_to_fixed16(uint64_t val)
{
	uint_fixed_16_16_t fp;
	WARN_ON(val > U32_MAX);
	fp.val = (uint32_t) val;
	return fp;
}