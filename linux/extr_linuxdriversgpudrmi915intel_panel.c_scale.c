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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST_ULL (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ clamp (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mul_u32_u32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static u32 scale(u32 source_val,
		 u32 source_min, u32 source_max,
		 u32 target_min, u32 target_max)
{
	u64 target_val;

	WARN_ON(source_min > source_max);
	WARN_ON(target_min > target_max);

	/* defensive */
	source_val = clamp(source_val, source_min, source_max);

	/* avoid overflows */
	target_val = mul_u32_u32(source_val - source_min,
				 target_max - target_min);
	target_val = DIV_ROUND_CLOSEST_ULL(target_val, source_max - source_min);
	target_val += target_min;

	return target_val;
}