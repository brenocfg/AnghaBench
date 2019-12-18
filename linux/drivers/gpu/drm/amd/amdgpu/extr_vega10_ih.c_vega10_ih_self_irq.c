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
typedef  void* uint32_t ;
struct amdgpu_iv_entry {int ring_id; int /*<<< orphan*/ * src_data; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_4__ {void** wptr_cpu; } ;
struct TYPE_5__ {void** wptr_cpu; } ;
struct TYPE_6__ {int /*<<< orphan*/  ih2_work; TYPE_1__ ih2; int /*<<< orphan*/  ih1_work; TYPE_2__ ih1; } ;
struct amdgpu_device {TYPE_3__ irq; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vega10_ih_self_irq(struct amdgpu_device *adev,
			      struct amdgpu_irq_src *source,
			      struct amdgpu_iv_entry *entry)
{
	uint32_t wptr = cpu_to_le32(entry->src_data[0]);

	switch (entry->ring_id) {
	case 1:
		*adev->irq.ih1.wptr_cpu = wptr;
		schedule_work(&adev->irq.ih1_work);
		break;
	case 2:
		*adev->irq.ih2.wptr_cpu = wptr;
		schedule_work(&adev->irq.ih2_work);
		break;
	default: break;
	}
	return 0;
}