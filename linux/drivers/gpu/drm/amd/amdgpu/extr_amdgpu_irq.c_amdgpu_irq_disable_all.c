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
struct amdgpu_irq_src {unsigned int num_types; TYPE_2__* funcs; int /*<<< orphan*/ * enabled_types; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__* client; } ;
struct amdgpu_device {TYPE_3__ irq; } ;
struct TYPE_5__ {int (* set ) (struct amdgpu_device*,struct amdgpu_irq_src*,unsigned int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct amdgpu_irq_src** sources; } ;

/* Variables and functions */
 unsigned int AMDGPU_IRQ_CLIENTID_MAX ; 
 int /*<<< orphan*/  AMDGPU_IRQ_STATE_DISABLE ; 
 unsigned int AMDGPU_MAX_IRQ_SRC_ID ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct amdgpu_device*,struct amdgpu_irq_src*,unsigned int,int /*<<< orphan*/ ) ; 

void amdgpu_irq_disable_all(struct amdgpu_device *adev)
{
	unsigned long irqflags;
	unsigned i, j, k;
	int r;

	spin_lock_irqsave(&adev->irq.lock, irqflags);
	for (i = 0; i < AMDGPU_IRQ_CLIENTID_MAX; ++i) {
		if (!adev->irq.client[i].sources)
			continue;

		for (j = 0; j < AMDGPU_MAX_IRQ_SRC_ID; ++j) {
			struct amdgpu_irq_src *src = adev->irq.client[i].sources[j];

			if (!src || !src->funcs->set || !src->num_types)
				continue;

			for (k = 0; k < src->num_types; ++k) {
				atomic_set(&src->enabled_types[k], 0);
				r = src->funcs->set(adev, src, k,
						    AMDGPU_IRQ_STATE_DISABLE);
				if (r)
					DRM_ERROR("error disabling interrupt (%d)\n",
						  r);
			}
		}
	}
	spin_unlock_irqrestore(&adev->irq.lock, irqflags);
}