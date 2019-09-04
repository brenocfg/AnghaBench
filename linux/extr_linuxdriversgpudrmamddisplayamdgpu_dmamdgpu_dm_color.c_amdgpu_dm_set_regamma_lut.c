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
typedef  int uint32_t ;
struct drm_property_blob {int length; scalar_t__ data; } ;
struct drm_color_lut {int dummy; } ;
struct TYPE_3__ {struct drm_property_blob* gamma_lut; } ;
struct dm_crtc_state {struct dc_stream_state* stream; TYPE_1__ base; } ;
struct dc_stream_state {TYPE_2__* out_transfer_func; } ;
struct dc_gamma {int num_entries; scalar_t__ type; } ;
typedef  enum dc_transfer_func_type { ____Placeholder_dc_transfer_func_type } dc_transfer_func_type ;
struct TYPE_4__ {int type; int /*<<< orphan*/  tf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ GAMMA_CS_TFM_1D ; 
 scalar_t__ GAMMA_RGB_256 ; 
 int MAX_COLOR_LEGACY_LUT_ENTRIES ; 
 int MAX_COLOR_LUT_ENTRIES ; 
 int TF_TYPE_DISTRIBUTED_POINTS ; 
 int TF_TYPE_PREDEFINED ; 
 int /*<<< orphan*/  TRANSFER_FUNCTION_SRGB ; 
 int /*<<< orphan*/  __drm_lut_to_dc_gamma (struct drm_color_lut*,struct dc_gamma*,int) ; 
 struct dc_gamma* dc_create_gamma () ; 
 int /*<<< orphan*/  dc_gamma_release (struct dc_gamma**) ; 
 int mod_color_calculate_regamma_params (TYPE_2__*,struct dc_gamma*,int) ; 

int amdgpu_dm_set_regamma_lut(struct dm_crtc_state *crtc)
{
	struct drm_property_blob *blob = crtc->base.gamma_lut;
	struct dc_stream_state *stream = crtc->stream;
	struct drm_color_lut *lut;
	uint32_t lut_size;
	struct dc_gamma *gamma;
	enum dc_transfer_func_type old_type = stream->out_transfer_func->type;

	bool ret;

	if (!blob) {
		/* By default, use the SRGB predefined curve.*/
		stream->out_transfer_func->type = TF_TYPE_PREDEFINED;
		stream->out_transfer_func->tf = TRANSFER_FUNCTION_SRGB;
		return 0;
	}

	lut = (struct drm_color_lut *)blob->data;
	lut_size = blob->length / sizeof(struct drm_color_lut);

	gamma = dc_create_gamma();
	if (!gamma)
		return -ENOMEM;

	gamma->num_entries = lut_size;
	if (gamma->num_entries == MAX_COLOR_LEGACY_LUT_ENTRIES)
		gamma->type = GAMMA_RGB_256;
	else if (gamma->num_entries == MAX_COLOR_LUT_ENTRIES)
		gamma->type = GAMMA_CS_TFM_1D;
	else {
		/* Invalid lut size */
		dc_gamma_release(&gamma);
		return -EINVAL;
	}

	/* Convert drm_lut into dc_gamma */
	__drm_lut_to_dc_gamma(lut, gamma, gamma->type == GAMMA_RGB_256);

	/* Call color module to translate into something DC understands. Namely
	 * a transfer function.
	 */
	stream->out_transfer_func->type = TF_TYPE_DISTRIBUTED_POINTS;
	ret = mod_color_calculate_regamma_params(stream->out_transfer_func,
						 gamma, true);
	dc_gamma_release(&gamma);
	if (!ret) {
		stream->out_transfer_func->type = old_type;
		DRM_ERROR("Out of memory when calculating regamma params\n");
		return -ENOMEM;
	}

	return 0;
}