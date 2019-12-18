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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ L3C_CNTR0_LOWER ; 

__attribute__((used)) static u32 hisi_l3c_pmu_get_counter_offset(int cntr_idx)
{
	return (L3C_CNTR0_LOWER + (cntr_idx * 8));
}