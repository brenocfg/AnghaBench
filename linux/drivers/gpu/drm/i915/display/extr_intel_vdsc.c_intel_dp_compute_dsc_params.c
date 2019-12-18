#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct intel_dp {int* dsc_dpcd; } ;
struct TYPE_9__ {int compressed_bpp; int /*<<< orphan*/  slice_count; } ;
struct TYPE_7__ {int crtc_vdisplay; int /*<<< orphan*/  crtc_hdisplay; } ;
struct TYPE_8__ {TYPE_1__ adjusted_mode; } ;
struct drm_dsc_config {int pic_height; int slice_height; int dsc_version_major; int dsc_version_minor; int convert_rgb; int simple_422; int vbr_enable; int block_pred_enable; int bits_per_pixel; int bits_per_component; int* rc_buf_thresh; int initial_offset; int rc_model_size; int initial_scale_value; int /*<<< orphan*/  mux_word_size; TYPE_4__* rc_range_params; int /*<<< orphan*/  rc_quant_incr_limit1; int /*<<< orphan*/  rc_quant_incr_limit0; int /*<<< orphan*/  flatness_max_qp; int /*<<< orphan*/  flatness_min_qp; int /*<<< orphan*/  initial_xmit_delay; int /*<<< orphan*/  first_line_bpg_offset; scalar_t__ line_buf_depth; int /*<<< orphan*/  pic_width; int /*<<< orphan*/  slice_width; } ;
struct intel_crtc_state {int pipe_bpp; TYPE_3__ dsc_params; TYPE_2__ base; struct drm_dsc_config dp_dsc_cfg; } ;
struct TYPE_12__ {int initial_offset; TYPE_5__* rc_range_params; int /*<<< orphan*/  rc_quant_incr_limit1; int /*<<< orphan*/  rc_quant_incr_limit0; int /*<<< orphan*/  flatness_max_qp; int /*<<< orphan*/  flatness_min_qp; int /*<<< orphan*/  initial_xmit_delay; int /*<<< orphan*/  first_line_bpg_offset; } ;
struct TYPE_11__ {int range_bpg_offset; int /*<<< orphan*/  range_max_qp; int /*<<< orphan*/  range_min_qp; } ;
struct TYPE_10__ {int range_bpg_offset; int /*<<< orphan*/  range_max_qp; int /*<<< orphan*/  range_min_qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DP_DSC_BLK_PREDICTION_IS_SUPPORTED ; 
 size_t DP_DSC_BLK_PREDICTION_SUPPORT ; 
 size_t DP_DSC_DEC_COLOR_FORMAT_CAP ; 
 int DP_DSC_MAJOR_MASK ; 
 int DP_DSC_MAJOR_SHIFT ; 
 int DP_DSC_MINOR_MASK ; 
 int DP_DSC_MINOR_SHIFT ; 
 size_t DP_DSC_REV ; 
 int DP_DSC_RGB ; 
 size_t DP_DSC_SUPPORT ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ DSC_1_1_MAX_LINEBUF_DEPTH_BITS ; 
 scalar_t__ DSC_1_2_MAX_LINEBUF_DEPTH_BITS ; 
 scalar_t__ DSC_1_2_MAX_LINEBUF_DEPTH_VAL ; 
 int /*<<< orphan*/  DSC_MUX_WORD_SIZE_12_BPC ; 
 int /*<<< orphan*/  DSC_MUX_WORD_SIZE_8_10_BPC ; 
 int DSC_NUM_BUF_RANGES ; 
 int DSC_RANGE_BPG_OFFSET_MASK ; 
 int DSC_RC_MODEL_SIZE_CONST ; 
 int /*<<< orphan*/  DSC_SUPPORTED_VERSION_MIN ; 
 int EINVAL ; 
 scalar_t__ drm_dp_dsc_sink_line_buf_depth (int*) ; 
 int drm_dsc_compute_rc_parameters (struct drm_dsc_config*) ; 
 int get_column_index_for_rc_params (int) ; 
 int get_row_index_for_rc_params (int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int* rc_buf_thresh ; 
 TYPE_6__** rc_params ; 

int intel_dp_compute_dsc_params(struct intel_dp *intel_dp,
				struct intel_crtc_state *pipe_config)
{
	struct drm_dsc_config *vdsc_cfg = &pipe_config->dp_dsc_cfg;
	u16 compressed_bpp = pipe_config->dsc_params.compressed_bpp;
	u8 i = 0;
	int row_index = 0;
	int column_index = 0;
	u8 line_buf_depth = 0;

	vdsc_cfg->pic_width = pipe_config->base.adjusted_mode.crtc_hdisplay;
	vdsc_cfg->pic_height = pipe_config->base.adjusted_mode.crtc_vdisplay;
	vdsc_cfg->slice_width = DIV_ROUND_UP(vdsc_cfg->pic_width,
					     pipe_config->dsc_params.slice_count);
	/*
	 * Slice Height of 8 works for all currently available panels. So start
	 * with that if pic_height is an integral multiple of 8.
	 * Eventually add logic to try multiple slice heights.
	 */
	if (vdsc_cfg->pic_height % 8 == 0)
		vdsc_cfg->slice_height = 8;
	else if (vdsc_cfg->pic_height % 4 == 0)
		vdsc_cfg->slice_height = 4;
	else
		vdsc_cfg->slice_height = 2;

	/* Values filled from DSC Sink DPCD */
	vdsc_cfg->dsc_version_major =
		(intel_dp->dsc_dpcd[DP_DSC_REV - DP_DSC_SUPPORT] &
		 DP_DSC_MAJOR_MASK) >> DP_DSC_MAJOR_SHIFT;
	vdsc_cfg->dsc_version_minor =
		min(DSC_SUPPORTED_VERSION_MIN,
		    (intel_dp->dsc_dpcd[DP_DSC_REV - DP_DSC_SUPPORT] &
		     DP_DSC_MINOR_MASK) >> DP_DSC_MINOR_SHIFT);

	vdsc_cfg->convert_rgb = intel_dp->dsc_dpcd[DP_DSC_DEC_COLOR_FORMAT_CAP - DP_DSC_SUPPORT] &
		DP_DSC_RGB;

	line_buf_depth = drm_dp_dsc_sink_line_buf_depth(intel_dp->dsc_dpcd);
	if (!line_buf_depth) {
		DRM_DEBUG_KMS("DSC Sink Line Buffer Depth invalid\n");
		return -EINVAL;
	}
	if (vdsc_cfg->dsc_version_minor == 2)
		vdsc_cfg->line_buf_depth = (line_buf_depth == DSC_1_2_MAX_LINEBUF_DEPTH_BITS) ?
			DSC_1_2_MAX_LINEBUF_DEPTH_VAL : line_buf_depth;
	else
		vdsc_cfg->line_buf_depth = (line_buf_depth > DSC_1_1_MAX_LINEBUF_DEPTH_BITS) ?
			DSC_1_1_MAX_LINEBUF_DEPTH_BITS : line_buf_depth;

	/* Gen 11 does not support YCbCr */
	vdsc_cfg->simple_422 = false;
	/* Gen 11 does not support VBR */
	vdsc_cfg->vbr_enable = false;
	vdsc_cfg->block_pred_enable =
			intel_dp->dsc_dpcd[DP_DSC_BLK_PREDICTION_SUPPORT - DP_DSC_SUPPORT] &
		DP_DSC_BLK_PREDICTION_IS_SUPPORTED;

	/* Gen 11 only supports integral values of bpp */
	vdsc_cfg->bits_per_pixel = compressed_bpp << 4;
	vdsc_cfg->bits_per_component = pipe_config->pipe_bpp / 3;

	for (i = 0; i < DSC_NUM_BUF_RANGES - 1; i++) {
		/*
		 * six 0s are appended to the lsb of each threshold value
		 * internally in h/w.
		 * Only 8 bits are allowed for programming RcBufThreshold
		 */
		vdsc_cfg->rc_buf_thresh[i] = rc_buf_thresh[i] >> 6;
	}

	/*
	 * For 6bpp, RC Buffer threshold 12 and 13 need a different value
	 * as per C Model
	 */
	if (compressed_bpp == 6) {
		vdsc_cfg->rc_buf_thresh[12] = 0x7C;
		vdsc_cfg->rc_buf_thresh[13] = 0x7D;
	}

	row_index = get_row_index_for_rc_params(compressed_bpp);
	column_index =
		get_column_index_for_rc_params(vdsc_cfg->bits_per_component);

	if (row_index < 0 || column_index < 0)
		return -EINVAL;

	vdsc_cfg->first_line_bpg_offset =
		rc_params[row_index][column_index].first_line_bpg_offset;
	vdsc_cfg->initial_xmit_delay =
		rc_params[row_index][column_index].initial_xmit_delay;
	vdsc_cfg->initial_offset =
		rc_params[row_index][column_index].initial_offset;
	vdsc_cfg->flatness_min_qp =
		rc_params[row_index][column_index].flatness_min_qp;
	vdsc_cfg->flatness_max_qp =
		rc_params[row_index][column_index].flatness_max_qp;
	vdsc_cfg->rc_quant_incr_limit0 =
		rc_params[row_index][column_index].rc_quant_incr_limit0;
	vdsc_cfg->rc_quant_incr_limit1 =
		rc_params[row_index][column_index].rc_quant_incr_limit1;

	for (i = 0; i < DSC_NUM_BUF_RANGES; i++) {
		vdsc_cfg->rc_range_params[i].range_min_qp =
			rc_params[row_index][column_index].rc_range_params[i].range_min_qp;
		vdsc_cfg->rc_range_params[i].range_max_qp =
			rc_params[row_index][column_index].rc_range_params[i].range_max_qp;
		/*
		 * Range BPG Offset uses 2's complement and is only a 6 bits. So
		 * mask it to get only 6 bits.
		 */
		vdsc_cfg->rc_range_params[i].range_bpg_offset =
			rc_params[row_index][column_index].rc_range_params[i].range_bpg_offset &
			DSC_RANGE_BPG_OFFSET_MASK;
	}

	/*
	 * BitsPerComponent value determines mux_word_size:
	 * When BitsPerComponent is 12bpc, muxWordSize will be equal to 64 bits
	 * When BitsPerComponent is 8 or 10bpc, muxWordSize will be equal to
	 * 48 bits
	 */
	if (vdsc_cfg->bits_per_component == 8 ||
	    vdsc_cfg->bits_per_component == 10)
		vdsc_cfg->mux_word_size = DSC_MUX_WORD_SIZE_8_10_BPC;
	else if (vdsc_cfg->bits_per_component == 12)
		vdsc_cfg->mux_word_size = DSC_MUX_WORD_SIZE_12_BPC;

	/* RC_MODEL_SIZE is a constant across all configurations */
	vdsc_cfg->rc_model_size = DSC_RC_MODEL_SIZE_CONST;
	/* InitialScaleValue is a 6 bit value with 3 fractional bits (U3.3) */
	vdsc_cfg->initial_scale_value = (vdsc_cfg->rc_model_size << 3) /
		(vdsc_cfg->rc_model_size - vdsc_cfg->initial_offset);

	return drm_dsc_compute_rc_parameters(vdsc_cfg);
}