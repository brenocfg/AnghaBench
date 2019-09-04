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
struct dpu_encoder_irq {int irq_idx; int /*<<< orphan*/  hw_idx; int /*<<< orphan*/  cb; } ;
typedef  enum dpu_intr_idx { ____Placeholder_dpu_intr_idx } dpu_intr_idx ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,...) ; 
 int EINVAL ; 
 int dpu_core_irq_disable (int /*<<< orphan*/ ,int*,int) ; 
 int dpu_core_irq_unregister_callback (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_dpu_enc_irq_unregister_success (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

int dpu_encoder_helper_unregister_irq(struct dpu_encoder_phys *phys_enc,
		enum dpu_intr_idx intr_idx)
{
	struct dpu_encoder_irq *irq;
	int ret;

	if (!phys_enc) {
		DPU_ERROR("invalid encoder\n");
		return -EINVAL;
	}
	irq = &phys_enc->irq[intr_idx];

	/* silently skip irqs that weren't registered */
	if (irq->irq_idx < 0) {
		DRM_ERROR("duplicate unregister id=%u, intr=%d, hw=%d, irq=%d",
			  DRMID(phys_enc->parent), intr_idx, irq->hw_idx,
			  irq->irq_idx);
		return 0;
	}

	ret = dpu_core_irq_disable(phys_enc->dpu_kms, &irq->irq_idx, 1);
	if (ret) {
		DRM_ERROR("disable failed id=%u, intr=%d, hw=%d, irq=%d ret=%d",
			  DRMID(phys_enc->parent), intr_idx, irq->hw_idx,
			  irq->irq_idx, ret);
	}

	ret = dpu_core_irq_unregister_callback(phys_enc->dpu_kms, irq->irq_idx,
			&irq->cb);
	if (ret) {
		DRM_ERROR("unreg cb fail id=%u, intr=%d, hw=%d, irq=%d ret=%d",
			  DRMID(phys_enc->parent), intr_idx, irq->hw_idx,
			  irq->irq_idx, ret);
	}

	trace_dpu_enc_irq_unregister_success(DRMID(phys_enc->parent), intr_idx,
					     irq->hw_idx, irq->irq_idx);

	irq->irq_idx = -EINVAL;

	return 0;
}