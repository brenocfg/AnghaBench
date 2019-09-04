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
struct dpu_encoder_phys {int /*<<< orphan*/  intf_idx; struct dpu_encoder_irq* irq; } ;
struct dpu_encoder_irq {scalar_t__ irq_idx; int /*<<< orphan*/  hw_idx; } ;

/* Variables and functions */
 size_t INTR_IDX_UNDERRUN ; 
 size_t INTR_IDX_VSYNC ; 

__attribute__((used)) static void _dpu_encoder_phys_vid_setup_irq_hw_idx(
		struct dpu_encoder_phys *phys_enc)
{
	struct dpu_encoder_irq *irq;

	/*
	 * Initialize irq->hw_idx only when irq is not registered.
	 * Prevent invalidating irq->irq_idx as modeset may be
	 * called many times during dfps.
	 */

	irq = &phys_enc->irq[INTR_IDX_VSYNC];
	if (irq->irq_idx < 0)
		irq->hw_idx = phys_enc->intf_idx;

	irq = &phys_enc->irq[INTR_IDX_UNDERRUN];
	if (irq->irq_idx < 0)
		irq->hw_idx = phys_enc->intf_idx;
}