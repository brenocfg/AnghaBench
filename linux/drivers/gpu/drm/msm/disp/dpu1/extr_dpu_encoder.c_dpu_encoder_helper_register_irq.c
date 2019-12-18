#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dpu_encoder_phys {int /*<<< orphan*/  parent; int /*<<< orphan*/  dpu_kms; struct dpu_encoder_irq* irq; } ;
struct dpu_encoder_irq {int irq_idx; int /*<<< orphan*/  hw_idx; int /*<<< orphan*/  cb; int /*<<< orphan*/  name; int /*<<< orphan*/  intr_type; } ;
typedef  enum dpu_intr_idx { ____Placeholder_dpu_intr_idx } dpu_intr_idx ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_PHYS (struct dpu_encoder_phys*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_ERROR_PHYS (struct dpu_encoder_phys*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int INTR_IDX_MAX ; 
 int dpu_core_irq_enable (int /*<<< orphan*/ ,int*,int) ; 
 int dpu_core_irq_idx_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpu_core_irq_register_callback (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_core_irq_unregister_callback (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_dpu_enc_irq_register_success (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

int dpu_encoder_helper_register_irq(struct dpu_encoder_phys *phys_enc,
		enum dpu_intr_idx intr_idx)
{
	struct dpu_encoder_irq *irq;
	int ret = 0;

	if (!phys_enc || intr_idx >= INTR_IDX_MAX) {
		DPU_ERROR("invalid params\n");
		return -EINVAL;
	}
	irq = &phys_enc->irq[intr_idx];

	if (irq->irq_idx >= 0) {
		DPU_DEBUG_PHYS(phys_enc,
				"skipping already registered irq %s type %d\n",
				irq->name, irq->intr_type);
		return 0;
	}

	irq->irq_idx = dpu_core_irq_idx_lookup(phys_enc->dpu_kms,
			irq->intr_type, irq->hw_idx);
	if (irq->irq_idx < 0) {
		DPU_ERROR_PHYS(phys_enc,
			"failed to lookup IRQ index for %s type:%d\n",
			irq->name, irq->intr_type);
		return -EINVAL;
	}

	ret = dpu_core_irq_register_callback(phys_enc->dpu_kms, irq->irq_idx,
			&irq->cb);
	if (ret) {
		DPU_ERROR_PHYS(phys_enc,
			"failed to register IRQ callback for %s\n",
			irq->name);
		irq->irq_idx = -EINVAL;
		return ret;
	}

	ret = dpu_core_irq_enable(phys_enc->dpu_kms, &irq->irq_idx, 1);
	if (ret) {
		DRM_ERROR("enable failed id=%u, intr=%d, hw=%d, irq=%d",
			  DRMID(phys_enc->parent), intr_idx, irq->hw_idx,
			  irq->irq_idx);
		dpu_core_irq_unregister_callback(phys_enc->dpu_kms,
				irq->irq_idx, &irq->cb);
		irq->irq_idx = -EINVAL;
		return ret;
	}

	trace_dpu_enc_irq_register_success(DRMID(phys_enc->parent), intr_idx,
				irq->hw_idx, irq->irq_idx);

	return ret;
}