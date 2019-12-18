#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct msm_drm_private {int dummy; } ;
struct dpu_encoder_phys {scalar_t__ hw_ctl; scalar_t__ enable_state; TYPE_3__* hw_intf; TYPE_4__* parent; int /*<<< orphan*/  pending_kickoff_cnt; int /*<<< orphan*/  enc_spinlock; } ;
struct TYPE_8__ {TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* enable_timing ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {scalar_t__ idx; TYPE_2__ ops; } ;
struct TYPE_5__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ DPU_ENC_DISABLED ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRMID (TYPE_4__*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ INTF_0 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_encoder_phys_inc_pending (struct dpu_encoder_phys*) ; 
 scalar_t__ dpu_encoder_phys_vid_is_master (struct dpu_encoder_phys*) ; 
 int dpu_encoder_phys_vid_wait_for_vblank (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpu_encoder_phys_vid_disable(struct dpu_encoder_phys *phys_enc)
{
	struct msm_drm_private *priv;
	unsigned long lock_flags;
	int ret;

	if (!phys_enc || !phys_enc->parent || !phys_enc->parent->dev ||
			!phys_enc->parent->dev->dev_private) {
		DPU_ERROR("invalid encoder/device\n");
		return;
	}
	priv = phys_enc->parent->dev->dev_private;

	if (!phys_enc->hw_intf || !phys_enc->hw_ctl) {
		DPU_ERROR("invalid hw_intf %d hw_ctl %d\n",
				phys_enc->hw_intf != 0, phys_enc->hw_ctl != 0);
		return;
	}

	if (WARN_ON(!phys_enc->hw_intf->ops.enable_timing))
		return;

	if (phys_enc->enable_state == DPU_ENC_DISABLED) {
		DPU_ERROR("already disabled\n");
		return;
	}

	spin_lock_irqsave(phys_enc->enc_spinlock, lock_flags);
	phys_enc->hw_intf->ops.enable_timing(phys_enc->hw_intf, 0);
	if (dpu_encoder_phys_vid_is_master(phys_enc))
		dpu_encoder_phys_inc_pending(phys_enc);
	spin_unlock_irqrestore(phys_enc->enc_spinlock, lock_flags);

	/*
	 * Wait for a vsync so we know the ENABLE=0 latched before
	 * the (connector) source of the vsync's gets disabled,
	 * otherwise we end up in a funny state if we re-enable
	 * before the disable latches, which results that some of
	 * the settings changes for the new modeset (like new
	 * scanout buffer) don't latch properly..
	 */
	if (dpu_encoder_phys_vid_is_master(phys_enc)) {
		ret = dpu_encoder_phys_vid_wait_for_vblank(phys_enc);
		if (ret) {
			atomic_set(&phys_enc->pending_kickoff_cnt, 0);
			DRM_ERROR("wait disable failed: id:%u intf:%d ret:%d\n",
				  DRMID(phys_enc->parent),
				  phys_enc->hw_intf->idx - INTF_0, ret);
		}
	}

	phys_enc->enable_state = DPU_ENC_DISABLED;
}