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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ srbm_soft_reset; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;

/* Variables and functions */
 scalar_t__ REG_GET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFT_RESET_SDMA ; 
 int /*<<< orphan*/  SOFT_RESET_SDMA1 ; 
 int /*<<< orphan*/  SRBM_SOFT_RESET ; 
 int /*<<< orphan*/  sdma_v3_0_gfx_resume (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sdma_v3_0_rlc_resume (struct amdgpu_device*) ; 

__attribute__((used)) static int sdma_v3_0_post_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;

	if (!adev->sdma.srbm_soft_reset)
		return 0;

	srbm_soft_reset = adev->sdma.srbm_soft_reset;

	if (REG_GET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_SDMA) ||
	    REG_GET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_SDMA1)) {
		sdma_v3_0_gfx_resume(adev);
		sdma_v3_0_rlc_resume(adev);
	}

	return 0;
}