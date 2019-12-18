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
struct amdgpu_iv_entry {int src_id; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_6__ {int high_to_low; int /*<<< orphan*/  work; } ;
struct TYPE_4__ {TYPE_3__ thermal; } ;
struct TYPE_5__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kv_dpm_process_interrupt(struct amdgpu_device *adev,
				    struct amdgpu_irq_src *source,
				    struct amdgpu_iv_entry *entry)
{
	bool queue_thermal = false;

	if (entry == NULL)
		return -EINVAL;

	switch (entry->src_id) {
	case 230: /* thermal low to high */
		DRM_DEBUG("IH: thermal low to high\n");
		adev->pm.dpm.thermal.high_to_low = false;
		queue_thermal = true;
		break;
	case 231: /* thermal high to low */
		DRM_DEBUG("IH: thermal high to low\n");
		adev->pm.dpm.thermal.high_to_low = true;
		queue_thermal = true;
		break;
	default:
		break;
	}

	if (queue_thermal)
		schedule_work(&adev->pm.dpm.thermal.work);

	return 0;
}