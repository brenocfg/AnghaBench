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
struct dpu_encoder_phys {scalar_t__ enable_state; scalar_t__ split_role; TYPE_2__* parent; } ;
struct dpu_crtc_state {scalar_t__ num_mixers; } ;
typedef  enum dpu_3d_blend_mode { ____Placeholder_dpu_3d_blend_mode } dpu_3d_blend_mode ;
struct TYPE_4__ {TYPE_1__* crtc; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int BLEND_3D_H_ROW_INT ; 
 int BLEND_3D_NONE ; 
 scalar_t__ CRTC_DUAL_MIXERS ; 
 scalar_t__ DPU_ENC_DISABLING ; 
 scalar_t__ ENC_ROLE_SOLO ; 
 struct dpu_crtc_state* to_dpu_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum dpu_3d_blend_mode dpu_encoder_helper_get_3d_blend_mode(
		struct dpu_encoder_phys *phys_enc)
{
	struct dpu_crtc_state *dpu_cstate;

	if (!phys_enc || phys_enc->enable_state == DPU_ENC_DISABLING)
		return BLEND_3D_NONE;

	dpu_cstate = to_dpu_crtc_state(phys_enc->parent->crtc->state);

	if (phys_enc->split_role == ENC_ROLE_SOLO &&
	    dpu_cstate->num_mixers == CRTC_DUAL_MIXERS)
		return BLEND_3D_H_ROW_INT;

	return BLEND_3D_NONE;
}