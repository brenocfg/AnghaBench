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
struct dpu_encoder_phys {int /*<<< orphan*/  parent; TYPE_2__* parent_ops; TYPE_1__* hw_pp; scalar_t__ intf_idx; } ;
typedef  enum dpu_intr_idx { ____Placeholder_dpu_intr_idx } dpu_intr_idx ;
struct TYPE_4__ {int /*<<< orphan*/  (* handle_frame_done ) (int /*<<< orphan*/ ,struct dpu_encoder_phys*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ENCODER_FRAME_EVENT_ERROR ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ INTF_0 ; 
 scalar_t__ PINGPONG_0 ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 

void dpu_encoder_helper_report_irq_timeout(struct dpu_encoder_phys *phys_enc,
		enum dpu_intr_idx intr_idx)
{
	DRM_ERROR("irq timeout id=%u, intf=%d, pp=%d, intr=%d\n",
		  DRMID(phys_enc->parent), phys_enc->intf_idx - INTF_0,
		  phys_enc->hw_pp->idx - PINGPONG_0, intr_idx);

	if (phys_enc->parent_ops->handle_frame_done)
		phys_enc->parent_ops->handle_frame_done(
				phys_enc->parent, phys_enc,
				DPU_ENCODER_FRAME_EVENT_ERROR);
}