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
struct dpu_encoder_phys {scalar_t__ enable_state; int /*<<< orphan*/  enc_spinlock; TYPE_2__* hw_intf; int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_timing ) (TYPE_2__*,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; scalar_t__ idx; } ;

/* Variables and functions */
 scalar_t__ DPU_ENC_ENABLED ; 
 scalar_t__ DPU_ENC_ENABLING ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 scalar_t__ INTF_0 ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  trace_dpu_enc_phys_vid_post_kickoff (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dpu_encoder_phys_vid_handle_post_kickoff(
		struct dpu_encoder_phys *phys_enc)
{
	unsigned long lock_flags;

	/*
	 * Video mode must flush CTL before enabling timing engine
	 * Video encoders need to turn on their interfaces now
	 */
	if (phys_enc->enable_state == DPU_ENC_ENABLING) {
		trace_dpu_enc_phys_vid_post_kickoff(DRMID(phys_enc->parent),
				    phys_enc->hw_intf->idx - INTF_0);
		spin_lock_irqsave(phys_enc->enc_spinlock, lock_flags);
		phys_enc->hw_intf->ops.enable_timing(phys_enc->hw_intf, 1);
		spin_unlock_irqrestore(phys_enc->enc_spinlock, lock_flags);
		phys_enc->enable_state = DPU_ENC_ENABLED;
	}
}