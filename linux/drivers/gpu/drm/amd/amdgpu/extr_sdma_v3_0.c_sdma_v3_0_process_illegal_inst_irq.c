#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct amdgpu_iv_entry {int ring_id; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_4__ {TYPE_3__* instance; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;
struct TYPE_5__ {int /*<<< orphan*/  sched; } ;
struct TYPE_6__ {TYPE_2__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  drm_sched_fault (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdma_v3_0_process_illegal_inst_irq(struct amdgpu_device *adev,
					      struct amdgpu_irq_src *source,
					      struct amdgpu_iv_entry *entry)
{
	u8 instance_id, queue_id;

	DRM_ERROR("Illegal instruction in SDMA command stream\n");
	instance_id = (entry->ring_id & 0x3) >> 0;
	queue_id = (entry->ring_id & 0xc) >> 2;

	if (instance_id <= 1 && queue_id == 0)
		drm_sched_fault(&adev->sdma.instance[instance_id].ring.sched);
	return 0;
}