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
struct amdgpu_device {scalar_t__ asic_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_ARCTURUS ; 
 int /*<<< orphan*/  athub_v1_0_get_clockgating (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmhub_v1_0_get_clockgating (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmhub_v9_4_get_clockgating (struct amdgpu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gmc_v9_0_get_clockgating_state(void *handle, u32 *flags)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->asic_type == CHIP_ARCTURUS)
		mmhub_v9_4_get_clockgating(adev, flags);
	else
		mmhub_v1_0_get_clockgating(adev, flags);

	athub_v1_0_get_clockgating(adev, flags);
}