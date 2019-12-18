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
typedef  int /*<<< orphan*/  uint64_t ;
struct kgd_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_gpu_clock_counter ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 

uint64_t amdgpu_amdkfd_get_gpu_clock_counter(struct kgd_dev *kgd)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;

	if (adev->gfx.funcs->get_gpu_clock_counter)
		return adev->gfx.funcs->get_gpu_clock_counter(adev);
	return 0;
}