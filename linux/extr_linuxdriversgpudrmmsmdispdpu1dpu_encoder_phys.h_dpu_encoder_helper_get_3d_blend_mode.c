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
struct dpu_encoder_phys {scalar_t__ enable_state; scalar_t__ split_role; scalar_t__ topology_name; } ;
typedef  enum dpu_3d_blend_mode { ____Placeholder_dpu_3d_blend_mode } dpu_3d_blend_mode ;

/* Variables and functions */
 int BLEND_3D_H_ROW_INT ; 
 int BLEND_3D_NONE ; 
 scalar_t__ DPU_ENC_DISABLING ; 
 scalar_t__ DPU_RM_TOPOLOGY_DUALPIPE_3DMERGE ; 
 scalar_t__ ENC_ROLE_SOLO ; 

__attribute__((used)) static inline enum dpu_3d_blend_mode dpu_encoder_helper_get_3d_blend_mode(
		struct dpu_encoder_phys *phys_enc)
{
	if (!phys_enc || phys_enc->enable_state == DPU_ENC_DISABLING)
		return BLEND_3D_NONE;

	if (phys_enc->split_role == ENC_ROLE_SOLO &&
	    phys_enc->topology_name == DPU_RM_TOPOLOGY_DUALPIPE_3DMERGE)
		return BLEND_3D_H_ROW_INT;

	return BLEND_3D_NONE;
}