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
struct TYPE_3__ {int /*<<< orphan*/ * man; } ;
struct TYPE_4__ {TYPE_1__ bdev; } ;
struct amdgpu_device {TYPE_2__ mman; } ;

/* Variables and functions */
 size_t TTM_PL_VRAM ; 
 int /*<<< orphan*/  amdgpu_vram_mgr_usage (int /*<<< orphan*/ *) ; 

uint64_t amdgpu_amdkfd_get_vram_usage(struct kgd_dev *kgd)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;

	return amdgpu_vram_mgr_usage(&adev->mman.bdev.man[TTM_PL_VRAM]);
}