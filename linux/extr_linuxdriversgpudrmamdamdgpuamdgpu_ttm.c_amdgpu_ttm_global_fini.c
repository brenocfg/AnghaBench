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
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;
struct TYPE_4__ {int mem_global_referenced; int /*<<< orphan*/  mem_global_ref; TYPE_1__ bo_global_ref; int /*<<< orphan*/  gtt_window_lock; } ;
struct amdgpu_device {TYPE_2__ mman; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_global_item_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_ttm_global_fini(struct amdgpu_device *adev)
{
	if (adev->mman.mem_global_referenced) {
		mutex_destroy(&adev->mman.gtt_window_lock);
		drm_global_item_unref(&adev->mman.bo_global_ref.ref);
		drm_global_item_unref(&adev->mman.mem_global_ref);
		adev->mman.mem_global_referenced = false;
	}
}