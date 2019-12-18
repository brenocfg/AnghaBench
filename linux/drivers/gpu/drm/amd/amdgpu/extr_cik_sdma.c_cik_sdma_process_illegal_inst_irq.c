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
typedef  size_t u8 ;
struct amdgpu_iv_entry {int ring_id; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_6__ {TYPE_2__* instance; } ;
struct amdgpu_device {TYPE_3__ sdma; } ;
struct TYPE_4__ {int /*<<< orphan*/  sched; } ;
struct TYPE_5__ {TYPE_1__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  drm_sched_fault (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cik_sdma_process_illegal_inst_irq(struct amdgpu_device *adev,
					     struct amdgpu_irq_src *source,
					     struct amdgpu_iv_entry *entry)
{
	u8 instance_id;

	DRM_ERROR("Illegal instruction in SDMA command stream\n");
	instance_id = (entry->ring_id & 0x3) >> 0;
	drm_sched_fault(&adev->sdma.instance[instance_id].ring.sched);
	return 0;
}