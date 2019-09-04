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
struct TYPE_4__ {int /*<<< orphan*/ * enable_counts; } ;
struct dpu_kms {TYPE_3__* hw_intr; TYPE_1__ irq_obj; } ;
struct TYPE_5__ {int (* disable_irq ) (TYPE_3__*,int) ;} ;
struct TYPE_6__ {int irq_idx_tbl_size; TYPE_2__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,int,int) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int EINVAL ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  trace_dpu_core_irq_disable_idx (int,int) ; 

__attribute__((used)) static int _dpu_core_irq_disable(struct dpu_kms *dpu_kms, int irq_idx)
{
	int ret = 0, enable_count;

	if (!dpu_kms || !dpu_kms->hw_intr || !dpu_kms->irq_obj.enable_counts) {
		DPU_ERROR("invalid params\n");
		return -EINVAL;
	}

	if (irq_idx < 0 || irq_idx >= dpu_kms->hw_intr->irq_idx_tbl_size) {
		DPU_ERROR("invalid IRQ index: [%d]\n", irq_idx);
		return -EINVAL;
	}

	enable_count = atomic_read(&dpu_kms->irq_obj.enable_counts[irq_idx]);
	DRM_DEBUG_KMS("irq_idx=%d enable_count=%d\n", irq_idx, enable_count);
	trace_dpu_core_irq_disable_idx(irq_idx, enable_count);

	if (atomic_dec_return(&dpu_kms->irq_obj.enable_counts[irq_idx]) == 0) {
		ret = dpu_kms->hw_intr->ops.disable_irq(
				dpu_kms->hw_intr,
				irq_idx);
		if (ret)
			DPU_ERROR("Fail to disable IRQ for irq_idx:%d\n",
					irq_idx);
		DPU_DEBUG("irq_idx=%d ret=%d\n", irq_idx, ret);
	}

	return ret;
}