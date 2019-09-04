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
struct TYPE_5__ {int /*<<< orphan*/  cb_lock; int /*<<< orphan*/ * irq_cb_tbl; int /*<<< orphan*/ * enable_counts; int /*<<< orphan*/  irq_counts; } ;
struct dpu_kms {TYPE_2__ irq_obj; TYPE_3__* hw_intr; } ;
struct TYPE_4__ {int (* enable_irq ) (TYPE_3__*,int) ;} ;
struct TYPE_6__ {int irq_idx_tbl_size; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,int,int) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int EINVAL ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  trace_dpu_core_irq_enable_idx (int,int) ; 

__attribute__((used)) static int _dpu_core_irq_enable(struct dpu_kms *dpu_kms, int irq_idx)
{
	unsigned long irq_flags;
	int ret = 0, enable_count;

	if (!dpu_kms || !dpu_kms->hw_intr ||
			!dpu_kms->irq_obj.enable_counts ||
			!dpu_kms->irq_obj.irq_counts) {
		DPU_ERROR("invalid params\n");
		return -EINVAL;
	}

	if (irq_idx < 0 || irq_idx >= dpu_kms->hw_intr->irq_idx_tbl_size) {
		DPU_ERROR("invalid IRQ index: [%d]\n", irq_idx);
		return -EINVAL;
	}

	enable_count = atomic_read(&dpu_kms->irq_obj.enable_counts[irq_idx]);
	DRM_DEBUG_KMS("irq_idx=%d enable_count=%d\n", irq_idx, enable_count);
	trace_dpu_core_irq_enable_idx(irq_idx, enable_count);

	if (atomic_inc_return(&dpu_kms->irq_obj.enable_counts[irq_idx]) == 1) {
		ret = dpu_kms->hw_intr->ops.enable_irq(
				dpu_kms->hw_intr,
				irq_idx);
		if (ret)
			DPU_ERROR("Fail to enable IRQ for irq_idx:%d\n",
					irq_idx);

		DPU_DEBUG("irq_idx=%d ret=%d\n", irq_idx, ret);

		spin_lock_irqsave(&dpu_kms->irq_obj.cb_lock, irq_flags);
		/* empty callback list but interrupt is enabled */
		if (list_empty(&dpu_kms->irq_obj.irq_cb_tbl[irq_idx]))
			DPU_ERROR("irq_idx=%d enabled with no callback\n",
					irq_idx);
		spin_unlock_irqrestore(&dpu_kms->irq_obj.cb_lock, irq_flags);
	}

	return ret;
}