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
struct dpu_encoder_virt {int num_phys_encs; struct dpu_encoder_phys** phys_encs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_hw_resources ) (struct dpu_encoder_phys*,struct dpu_encoder_hw_resources*) ;} ;
struct dpu_encoder_phys {TYPE_1__ ops; } ;
struct dpu_encoder_hw_resources {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_ENC (struct dpu_encoder_virt*,char*) ; 
 int /*<<< orphan*/  memset (struct dpu_encoder_hw_resources*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dpu_encoder_phys*,struct dpu_encoder_hw_resources*) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 

void dpu_encoder_get_hw_resources(struct drm_encoder *drm_enc,
				  struct dpu_encoder_hw_resources *hw_res)
{
	struct dpu_encoder_virt *dpu_enc = NULL;
	int i = 0;

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	DPU_DEBUG_ENC(dpu_enc, "\n");

	/* Query resources used by phys encs, expected to be without overlap */
	memset(hw_res, 0, sizeof(*hw_res));

	for (i = 0; i < dpu_enc->num_phys_encs; i++) {
		struct dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		if (phys && phys->ops.get_hw_resources)
			phys->ops.get_hw_resources(phys, hw_res);
	}
}