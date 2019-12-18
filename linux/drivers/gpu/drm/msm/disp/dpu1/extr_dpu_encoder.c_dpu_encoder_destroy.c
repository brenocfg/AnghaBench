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
struct dpu_encoder_virt {int num_phys_encs; int /*<<< orphan*/  enc_lock; struct dpu_encoder_phys** phys_encs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct dpu_encoder_phys*) ;} ;
struct dpu_encoder_phys {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_ENC (struct dpu_encoder_virt*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_ERROR_ENC (struct dpu_encoder_virt*,char*,int) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dpu_encoder_phys*) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 

__attribute__((used)) static void dpu_encoder_destroy(struct drm_encoder *drm_enc)
{
	struct dpu_encoder_virt *dpu_enc = NULL;
	int i = 0;

	if (!drm_enc) {
		DPU_ERROR("invalid encoder\n");
		return;
	}

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	DPU_DEBUG_ENC(dpu_enc, "\n");

	mutex_lock(&dpu_enc->enc_lock);

	for (i = 0; i < dpu_enc->num_phys_encs; i++) {
		struct dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		if (phys && phys->ops.destroy) {
			phys->ops.destroy(phys);
			--dpu_enc->num_phys_encs;
			dpu_enc->phys_encs[i] = NULL;
		}
	}

	if (dpu_enc->num_phys_encs)
		DPU_ERROR_ENC(dpu_enc, "expected 0 num_phys_encs not %d\n",
				dpu_enc->num_phys_encs);
	dpu_enc->num_phys_encs = 0;
	mutex_unlock(&dpu_enc->enc_lock);

	drm_encoder_cleanup(drm_enc);
	mutex_destroy(&dpu_enc->enc_lock);
}