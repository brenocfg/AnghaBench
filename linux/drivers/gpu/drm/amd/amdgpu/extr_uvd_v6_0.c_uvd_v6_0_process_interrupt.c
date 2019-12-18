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
struct amdgpu_iv_entry {int src_id; int /*<<< orphan*/ * src_data; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_4__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ring_enc; int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_fence_process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvd_v6_0_enc_support (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v6_0_process_interrupt(struct amdgpu_device *adev,
				      struct amdgpu_irq_src *source,
				      struct amdgpu_iv_entry *entry)
{
	bool int_handled = true;
	DRM_DEBUG("IH: UVD TRAP\n");

	switch (entry->src_id) {
	case 124:
		amdgpu_fence_process(&adev->uvd.inst->ring);
		break;
	case 119:
		if (likely(uvd_v6_0_enc_support(adev)))
			amdgpu_fence_process(&adev->uvd.inst->ring_enc[0]);
		else
			int_handled = false;
		break;
	case 120:
		if (likely(uvd_v6_0_enc_support(adev)))
			amdgpu_fence_process(&adev->uvd.inst->ring_enc[1]);
		else
			int_handled = false;
		break;
	}

	if (false == int_handled)
			DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);

	return 0;
}