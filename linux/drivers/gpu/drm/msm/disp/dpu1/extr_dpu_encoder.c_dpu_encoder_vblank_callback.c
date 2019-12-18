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
struct drm_encoder {int dummy; } ;
struct dpu_encoder_virt {int /*<<< orphan*/  enc_spinlock; scalar_t__ crtc; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  vsync_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_crtc_vblank_callback (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 

__attribute__((used)) static void dpu_encoder_vblank_callback(struct drm_encoder *drm_enc,
		struct dpu_encoder_phys *phy_enc)
{
	struct dpu_encoder_virt *dpu_enc = NULL;
	unsigned long lock_flags;

	if (!drm_enc || !phy_enc)
		return;

	DPU_ATRACE_BEGIN("encoder_vblank_callback");
	dpu_enc = to_dpu_encoder_virt(drm_enc);

	spin_lock_irqsave(&dpu_enc->enc_spinlock, lock_flags);
	if (dpu_enc->crtc)
		dpu_crtc_vblank_callback(dpu_enc->crtc);
	spin_unlock_irqrestore(&dpu_enc->enc_spinlock, lock_flags);

	atomic_inc(&phy_enc->vsync_cnt);
	DPU_ATRACE_END("encoder_vblank_callback");
}