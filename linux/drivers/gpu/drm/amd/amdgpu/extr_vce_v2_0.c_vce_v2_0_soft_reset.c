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
 int /*<<< orphan*/  SOFT_RESET_VCE ; 
 int /*<<< orphan*/  SRBM_SOFT_RESET ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int vce_v2_0_start (struct amdgpu_device*) ; 

__attribute__((used)) static int vce_v2_0_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	WREG32_FIELD(SRBM_SOFT_RESET, SOFT_RESET_VCE, 1);
	mdelay(5);

	return vce_v2_0_start(adev);
}