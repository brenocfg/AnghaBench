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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARMV8_IDX_TO_COUNTER (int) ; 
 int BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int armv8pmu_counter_has_overflowed(u32 pmnc, int idx)
{
	return pmnc & BIT(ARMV8_IDX_TO_COUNTER(idx));
}