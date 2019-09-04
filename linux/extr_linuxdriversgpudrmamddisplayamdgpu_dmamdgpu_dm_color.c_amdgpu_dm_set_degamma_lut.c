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
typedef  int uint32_t ;
struct drm_property_blob {int length; scalar_t__ data; } ;
struct drm_crtc_state {struct drm_property_blob* degamma_lut; } ;
struct drm_color_lut {int dummy; } ;
struct dc_plane_state {TYPE_1__* in_transfer_func; } ;
struct dc_gamma {int num_entries; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {void* type; int /*<<< orphan*/  tf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GAMMA_CUSTOM ; 
 int MAX_COLOR_LUT_ENTRIES ; 
 void* TF_TYPE_BYPASS ; 
 void* TF_TYPE_DISTRIBUTED_POINTS ; 
 void* TF_TYPE_PREDEFINED ; 
 int /*<<< orphan*/  TRANSFER_FUNCTION_LINEAR ; 
 int /*<<< orphan*/  TRANSFER_FUNCTION_SRGB ; 
 int /*<<< orphan*/  __drm_lut_to_dc_gamma (struct drm_color_lut*,struct dc_gamma*,int) ; 
 scalar_t__ __is_lut_linear (struct drm_color_lut*,int) ; 
 struct dc_gamma* dc_create_gamma () ; 
 int /*<<< orphan*/  dc_gamma_release (struct dc_gamma**) ; 
 int mod_color_calculate_degamma_params (TYPE_1__*,struct dc_gamma*,int) ; 

int amdgpu_dm_set_degamma_lut(struct drm_crtc_state *crtc_state,
			      struct dc_plane_state *dc_plane_state)
{
	struct drm_property_blob *blob = crtc_state->degamma_lut;
	struct drm_color_lut *lut;
	uint32_t lut_size;
	struct dc_gamma *gamma;
	bool ret;

	if (!blob) {
		/* Default to SRGB */
		dc_plane_state->in_transfer_func->type = TF_TYPE_PREDEFINED;
		dc_plane_state->in_transfer_func->tf = TRANSFER_FUNCTION_SRGB;
		return 0;
	}

	lut = (struct drm_color_lut *)blob->data;
	if (__is_lut_linear(lut, MAX_COLOR_LUT_ENTRIES)) {
		dc_plane_state->in_transfer_func->type = TF_TYPE_BYPASS;
		dc_plane_state->in_transfer_func->tf = TRANSFER_FUNCTION_LINEAR;
		return 0;
	}

	gamma = dc_create_gamma();
	if (!gamma)
		return -ENOMEM;

	lut_size = blob->length / sizeof(struct drm_color_lut);
	gamma->num_entries = lut_size;
	if (gamma->num_entries == MAX_COLOR_LUT_ENTRIES)
		gamma->type = GAMMA_CUSTOM;
	else {
		dc_gamma_release(&gamma);
		return -EINVAL;
	}

	__drm_lut_to_dc_gamma(lut, gamma, false);

	dc_plane_state->in_transfer_func->type = TF_TYPE_DISTRIBUTED_POINTS;
	ret = mod_color_calculate_degamma_params(dc_plane_state->in_transfer_func, gamma, true);
	dc_gamma_release(&gamma);
	if (!ret) {
		dc_plane_state->in_transfer_func->type = TF_TYPE_BYPASS;
		DRM_ERROR("Out of memory when calculating degamma params\n");
		return -ENOMEM;
	}

	return 0;
}