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
struct dpu_encoder_virt {int num_phys_encs; struct dpu_encoder_phys** phys_encs; TYPE_1__* cur_master; } ;
struct dpu_encoder_phys {int intf_mode; } ;
typedef  enum dpu_intf_mode { ____Placeholder_dpu_intf_mode } dpu_intf_mode ;
struct TYPE_2__ {int intf_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int INTF_MODE_NONE ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 

enum dpu_intf_mode dpu_encoder_get_intf_mode(struct drm_encoder *encoder)
{
	struct dpu_encoder_virt *dpu_enc = NULL;
	int i;

	if (!encoder) {
		DPU_ERROR("invalid encoder\n");
		return INTF_MODE_NONE;
	}
	dpu_enc = to_dpu_encoder_virt(encoder);

	if (dpu_enc->cur_master)
		return dpu_enc->cur_master->intf_mode;

	for (i = 0; i < dpu_enc->num_phys_encs; i++) {
		struct dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		if (phys)
			return phys->intf_mode;
	}

	return INTF_MODE_NONE;
}