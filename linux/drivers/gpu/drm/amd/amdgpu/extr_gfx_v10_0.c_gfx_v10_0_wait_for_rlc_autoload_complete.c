#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {int usec_timeout; TYPE_1__ firmware; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_RLC_BACKDOOR_AUTO ; 
 int /*<<< orphan*/  BOOTLOAD_COMPLETE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GC ; 
 int REG_GET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RLC_RLCS_BOOTLOAD_STATUS ; 
 scalar_t__ RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gfx_v10_0_rlc_backdoor_autoload_config_ce_cache (struct amdgpu_device*) ; 
 int gfx_v10_0_rlc_backdoor_autoload_config_me_cache (struct amdgpu_device*) ; 
 int gfx_v10_0_rlc_backdoor_autoload_config_mec_cache (struct amdgpu_device*) ; 
 int gfx_v10_0_rlc_backdoor_autoload_config_pfp_cache (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmCP_STAT ; 
 int /*<<< orphan*/  mmRLC_RLCS_BOOTLOAD_STATUS ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gfx_v10_0_wait_for_rlc_autoload_complete(struct amdgpu_device *adev)
{
	uint32_t cp_status;
	uint32_t bootload_status;
	int i, r;

	for (i = 0; i < adev->usec_timeout; i++) {
		cp_status = RREG32_SOC15(GC, 0, mmCP_STAT);
		bootload_status = RREG32_SOC15(GC, 0, mmRLC_RLCS_BOOTLOAD_STATUS);
		if ((cp_status == 0) &&
		    (REG_GET_FIELD(bootload_status,
			RLC_RLCS_BOOTLOAD_STATUS, BOOTLOAD_COMPLETE) == 1)) {
			break;
		}
		udelay(1);
	}

	if (i >= adev->usec_timeout) {
		dev_err(adev->dev, "rlc autoload: gc ucode autoload timeout\n");
		return -ETIMEDOUT;
	}

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_RLC_BACKDOOR_AUTO) {
		r = gfx_v10_0_rlc_backdoor_autoload_config_me_cache(adev);
		if (r)
			return r;

		r = gfx_v10_0_rlc_backdoor_autoload_config_ce_cache(adev);
		if (r)
			return r;

		r = gfx_v10_0_rlc_backdoor_autoload_config_pfp_cache(adev);
		if (r)
			return r;

		r = gfx_v10_0_rlc_backdoor_autoload_config_mec_cache(adev);
		if (r)
			return r;
	}

	return 0;
}