#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_encoder {int dummy; } ;
struct dpu_encoder_virt {void (* crtc_vblank_cb ) (void*) ;int num_phys_encs; struct dpu_encoder_phys** phys_encs; int /*<<< orphan*/  enc_spinlock; void* crtc_vblank_cb_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* control_vblank_irq ) (struct dpu_encoder_phys*,int) ;} ;
struct dpu_encoder_phys {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DRMID (struct drm_encoder*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct dpu_encoder_phys*,int) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 
 int /*<<< orphan*/  trace_dpu_enc_vblank_cb (int /*<<< orphan*/ ,int) ; 

void dpu_encoder_register_vblank_callback(struct drm_encoder *drm_enc,
		void (*vbl_cb)(void *), void *vbl_data)
{
	struct dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(drm_enc);
	unsigned long lock_flags;
	bool enable;
	int i;

	enable = vbl_cb ? true : false;

	if (!drm_enc) {
		DPU_ERROR("invalid encoder\n");
		return;
	}
	trace_dpu_enc_vblank_cb(DRMID(drm_enc), enable);

	spin_lock_irqsave(&dpu_enc->enc_spinlock, lock_flags);
	dpu_enc->crtc_vblank_cb = vbl_cb;
	dpu_enc->crtc_vblank_cb_data = vbl_data;
	spin_unlock_irqrestore(&dpu_enc->enc_spinlock, lock_flags);

	for (i = 0; i < dpu_enc->num_phys_encs; i++) {
		struct dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		if (phys && phys->ops.control_vblank_irq)
			phys->ops.control_vblank_irq(phys, enable);
	}
}