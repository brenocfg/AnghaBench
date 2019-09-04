#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * enable_counts; } ;
struct dpu_kms {TYPE_1__ irq_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINVAL ; 
 int _dpu_core_irq_disable (struct dpu_kms*,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

int dpu_core_irq_disable(struct dpu_kms *dpu_kms, int *irq_idxs, u32 irq_count)
{
	int i, ret = 0, counts;

	if (!dpu_kms || !irq_idxs || !irq_count) {
		DPU_ERROR("invalid params\n");
		return -EINVAL;
	}

	counts = atomic_read(&dpu_kms->irq_obj.enable_counts[irq_idxs[0]]);
	if (counts == 2)
		DRM_ERROR("irq_idx=%d enable_count=%d\n", irq_idxs[0], counts);

	for (i = 0; (i < irq_count) && !ret; i++)
		ret = _dpu_core_irq_disable(dpu_kms, irq_idxs[i]);

	return ret;
}