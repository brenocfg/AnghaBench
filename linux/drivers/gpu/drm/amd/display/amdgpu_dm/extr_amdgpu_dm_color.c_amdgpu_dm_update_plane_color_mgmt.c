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
typedef  scalar_t__ uint32_t ;
struct drm_color_lut {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  degamma_lut; } ;
struct dm_crtc_state {scalar_t__ cm_is_degamma_srgb; TYPE_1__ base; scalar_t__ cm_has_degamma; } ;
struct dc_plane_state {TYPE_2__* in_transfer_func; } ;
struct TYPE_4__ {void* tf; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ MAX_COLOR_LUT_ENTRIES ; 
 int /*<<< orphan*/  TF_TYPE_BYPASS ; 
 int /*<<< orphan*/  TF_TYPE_DISTRIBUTED_POINTS ; 
 int /*<<< orphan*/  TF_TYPE_PREDEFINED ; 
 void* TRANSFER_FUNCTION_LINEAR ; 
 void* TRANSFER_FUNCTION_SRGB ; 
 struct drm_color_lut* __extract_blob_lut (int /*<<< orphan*/ ,scalar_t__*) ; 
 int __set_input_tf (TYPE_2__*,struct drm_color_lut const*,scalar_t__) ; 

int amdgpu_dm_update_plane_color_mgmt(struct dm_crtc_state *crtc,
				      struct dc_plane_state *dc_plane_state)
{
	const struct drm_color_lut *degamma_lut;
	uint32_t degamma_size;
	int r;

	if (crtc->cm_has_degamma) {
		degamma_lut = __extract_blob_lut(crtc->base.degamma_lut,
						 &degamma_size);
		ASSERT(degamma_size == MAX_COLOR_LUT_ENTRIES);

		dc_plane_state->in_transfer_func->type =
			TF_TYPE_DISTRIBUTED_POINTS;

		/*
		 * This case isn't fully correct, but also fairly
		 * uncommon. This is userspace trying to use a
		 * legacy gamma LUT + atomic degamma LUT
		 * at the same time.
		 *
		 * Legacy gamma requires the input to be in linear
		 * space, so that means we need to apply an sRGB
		 * degamma. But color module also doesn't support
		 * a user ramp in this case so the degamma will
		 * be lost.
		 *
		 * Even if we did support it, it's still not right:
		 *
		 * Input -> CRTC DGM -> sRGB DGM -> CRTC CTM ->
		 * sRGB RGM -> CRTC RGM -> Output
		 *
		 * The CSC will be done in the wrong space since
		 * we're applying an sRGB DGM on top of the CRTC
		 * DGM.
		 *
		 * TODO: Don't use the legacy gamma interface and just
		 * map these to the atomic one instead.
		 */
		if (crtc->cm_is_degamma_srgb)
			dc_plane_state->in_transfer_func->tf =
				TRANSFER_FUNCTION_SRGB;
		else
			dc_plane_state->in_transfer_func->tf =
				TRANSFER_FUNCTION_LINEAR;

		r = __set_input_tf(dc_plane_state->in_transfer_func,
				   degamma_lut, degamma_size);
		if (r)
			return r;
	} else if (crtc->cm_is_degamma_srgb) {
		/*
		 * For legacy gamma support we need the regamma input
		 * in linear space. Assume that the input is sRGB.
		 */
		dc_plane_state->in_transfer_func->type = TF_TYPE_PREDEFINED;
		dc_plane_state->in_transfer_func->tf = TRANSFER_FUNCTION_SRGB;
	} else {
		/* ...Otherwise we can just bypass the DGM block. */
		dc_plane_state->in_transfer_func->type = TF_TYPE_BYPASS;
		dc_plane_state->in_transfer_func->tf = TRANSFER_FUNCTION_LINEAR;
	}

	return 0;
}