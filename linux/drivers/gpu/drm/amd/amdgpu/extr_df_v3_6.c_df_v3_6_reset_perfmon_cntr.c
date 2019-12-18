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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  df_v3_6_perfmon_wreg (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  df_v3_6_pmc_get_read_settings (struct amdgpu_device*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void df_v3_6_reset_perfmon_cntr(struct amdgpu_device *adev,
					 uint64_t config)
{
	uint32_t lo_base_addr, hi_base_addr;

	df_v3_6_pmc_get_read_settings(adev, config, &lo_base_addr,
				      &hi_base_addr);

	if ((lo_base_addr == 0) || (hi_base_addr == 0))
		return;

	df_v3_6_perfmon_wreg(adev, lo_base_addr, 0, hi_base_addr, 0);
}