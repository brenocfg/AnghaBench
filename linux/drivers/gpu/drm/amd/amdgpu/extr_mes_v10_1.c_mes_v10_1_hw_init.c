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
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  mes_v10_1_enable (struct amdgpu_device*,int) ; 
 int mes_v10_1_load_microcode (struct amdgpu_device*) ; 

__attribute__((used)) static int mes_v10_1_hw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT) {
		r = mes_v10_1_load_microcode(adev);
		if (r) {
			DRM_ERROR("failed to MES fw, r=%d\n", r);
			return r;
		}
	} else {
		DRM_ERROR("only support direct fw loading on MES\n");
		return -EINVAL;
	}

	mes_v10_1_enable(adev, true);

	return 0;
}