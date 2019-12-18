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
struct drm_crtc {int dummy; } ;
struct dpu_encoder_virt {int /*<<< orphan*/  enc_spinlock; struct drm_crtc* crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 

void dpu_encoder_assign_crtc(struct drm_encoder *drm_enc, struct drm_crtc *crtc)
{
	struct dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(drm_enc);
	unsigned long lock_flags;

	spin_lock_irqsave(&dpu_enc->enc_spinlock, lock_flags);
	/* crtc should always be cleared before re-assigning */
	WARN_ON(crtc && dpu_enc->crtc);
	dpu_enc->crtc = crtc;
	spin_unlock_irqrestore(&dpu_enc->enc_spinlock, lock_flags);
}