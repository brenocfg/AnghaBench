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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct ci_power_info {int /*<<< orphan*/  sram_end; scalar_t__ soft_regs_start; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int amdgpu_ci_read_smc_sram_dword (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_read_smc_soft_register(struct amdgpu_device *adev,
				     u16 reg_offset, u32 *value)
{
	struct ci_power_info *pi = ci_get_pi(adev);

	return amdgpu_ci_read_smc_sram_dword(adev,
				      pi->soft_regs_start + reg_offset,
				      value, pi->sram_end);
}