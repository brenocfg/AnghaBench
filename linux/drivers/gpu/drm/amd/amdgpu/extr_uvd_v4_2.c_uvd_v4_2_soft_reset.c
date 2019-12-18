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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmSRBM_SOFT_RESET ; 
 int uvd_v4_2_start (struct amdgpu_device*) ; 
 int /*<<< orphan*/  uvd_v4_2_stop (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v4_2_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	uvd_v4_2_stop(adev);

	WREG32_P(mmSRBM_SOFT_RESET, SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK,
			~SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK);
	mdelay(5);

	return uvd_v4_2_start(adev);
}