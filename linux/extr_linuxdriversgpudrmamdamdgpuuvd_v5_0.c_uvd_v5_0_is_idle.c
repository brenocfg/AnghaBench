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
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SRBM_STATUS__UVD_BUSY_MASK ; 
 int /*<<< orphan*/  mmSRBM_STATUS ; 

__attribute__((used)) static bool uvd_v5_0_is_idle(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	return !(RREG32(mmSRBM_STATUS) & SRBM_STATUS__UVD_BUSY_MASK);
}