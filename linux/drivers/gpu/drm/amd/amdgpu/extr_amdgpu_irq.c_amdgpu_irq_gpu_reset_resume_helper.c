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
struct amdgpu_irq_src {int num_types; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct amdgpu_device {TYPE_2__ irq; } ;
struct TYPE_3__ {struct amdgpu_irq_src** sources; } ;

/* Variables and functions */
 int AMDGPU_IRQ_CLIENTID_MAX ; 
 int AMDGPU_MAX_IRQ_SRC_ID ; 
 int /*<<< orphan*/  amdgpu_irq_update (struct amdgpu_device*,struct amdgpu_irq_src*,int) ; 

void amdgpu_irq_gpu_reset_resume_helper(struct amdgpu_device *adev)
{
	int i, j, k;

	for (i = 0; i < AMDGPU_IRQ_CLIENTID_MAX; ++i) {
		if (!adev->irq.client[i].sources)
			continue;

		for (j = 0; j < AMDGPU_MAX_IRQ_SRC_ID; ++j) {
			struct amdgpu_irq_src *src = adev->irq.client[i].sources[j];

			if (!src)
				continue;
			for (k = 0; k < src->num_types; k++)
				amdgpu_irq_update(adev, src, k);
		}
	}
}