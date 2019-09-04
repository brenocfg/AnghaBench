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
typedef  scalar_t__ u16 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SISLANDS_DPM2_PWREFFICIENCYRATIO_MARGIN ; 
 scalar_t__ div64_u64 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static u16 si_calculate_power_efficiency_ratio(struct amdgpu_device *adev,
					       const u16 prev_std_vddc,
					       const u16 curr_std_vddc)
{
	u64 margin = (u64)SISLANDS_DPM2_PWREFFICIENCYRATIO_MARGIN;
	u64 prev_vddc = (u64)prev_std_vddc;
	u64 curr_vddc = (u64)curr_std_vddc;
	u64 pwr_efficiency_ratio, n, d;

	if ((prev_vddc == 0) || (curr_vddc == 0))
		return 0;

	n = div64_u64((u64)1024 * curr_vddc * curr_vddc * ((u64)1000 + margin), (u64)1000);
	d = prev_vddc * prev_vddc;
	pwr_efficiency_ratio = div64_u64(n, d);

	if (pwr_efficiency_ratio > (u64)0xFFFF)
		return 0;

	return (u16)pwr_efficiency_ratio;
}