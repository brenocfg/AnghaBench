#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_mec; } ;
struct TYPE_4__ {TYPE_1__ mec; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_2__ gfx; } ;

/* Variables and functions */
 scalar_t__ CHIP_POLARIS11 ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int amdgpu_compute_multipipe ; 

__attribute__((used)) static bool amdgpu_gfx_is_multipipe_capable(struct amdgpu_device *adev)
{
	if (amdgpu_compute_multipipe != -1) {
		DRM_INFO("amdgpu: forcing compute pipe policy %d\n",
			 amdgpu_compute_multipipe);
		return amdgpu_compute_multipipe == 1;
	}

	/* FIXME: spreading the queues across pipes causes perf regressions
	 * on POLARIS11 compute workloads */
	if (adev->asic_type == CHIP_POLARIS11)
		return false;

	return adev->gfx.mec.num_mec > 1;
}