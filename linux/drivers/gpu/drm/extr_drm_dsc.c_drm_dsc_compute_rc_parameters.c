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
struct drm_dsc_config {int slice_width; unsigned long slice_chunk_size; int bits_per_pixel; int mux_word_size; int bits_per_component; int slice_height; int initial_scale_value; unsigned long scale_decrement_interval; scalar_t__ final_offset; scalar_t__ rc_model_size; int initial_xmit_delay; unsigned long nfl_bpg_offset; int first_line_bpg_offset; unsigned long slice_bpg_offset; unsigned long initial_offset; int scale_increment_interval; unsigned long rc_bits; unsigned long initial_dec_delay; scalar_t__ native_422; scalar_t__ convert_rgb; scalar_t__ native_420; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int DSC_RC_PIXELS_PER_GROUP ; 
 unsigned long DSC_SCALE_DECREMENT_INTERVAL_MAX ; 
 int ERANGE ; 

int drm_dsc_compute_rc_parameters(struct drm_dsc_config *vdsc_cfg)
{
	unsigned long groups_per_line = 0;
	unsigned long groups_total = 0;
	unsigned long num_extra_mux_bits = 0;
	unsigned long slice_bits = 0;
	unsigned long hrd_delay = 0;
	unsigned long final_scale = 0;
	unsigned long rbs_min = 0;

	if (vdsc_cfg->native_420 || vdsc_cfg->native_422) {
		/* Number of groups used to code each line of a slice */
		groups_per_line = DIV_ROUND_UP(vdsc_cfg->slice_width / 2,
					       DSC_RC_PIXELS_PER_GROUP);

		/* chunksize in Bytes */
		vdsc_cfg->slice_chunk_size = DIV_ROUND_UP(vdsc_cfg->slice_width / 2 *
							  vdsc_cfg->bits_per_pixel,
							  (8 * 16));
	} else {
		/* Number of groups used to code each line of a slice */
		groups_per_line = DIV_ROUND_UP(vdsc_cfg->slice_width,
					       DSC_RC_PIXELS_PER_GROUP);

		/* chunksize in Bytes */
		vdsc_cfg->slice_chunk_size = DIV_ROUND_UP(vdsc_cfg->slice_width *
							  vdsc_cfg->bits_per_pixel,
							  (8 * 16));
	}

	if (vdsc_cfg->convert_rgb)
		num_extra_mux_bits = 3 * (vdsc_cfg->mux_word_size +
					  (4 * vdsc_cfg->bits_per_component + 4)
					  - 2);
	else if (vdsc_cfg->native_422)
		num_extra_mux_bits = 4 * vdsc_cfg->mux_word_size +
			(4 * vdsc_cfg->bits_per_component + 4) +
			3 * (4 * vdsc_cfg->bits_per_component) - 2;
	else
		num_extra_mux_bits = 3 * vdsc_cfg->mux_word_size +
			(4 * vdsc_cfg->bits_per_component + 4) +
			2 * (4 * vdsc_cfg->bits_per_component) - 2;
	/* Number of bits in one Slice */
	slice_bits = 8 * vdsc_cfg->slice_chunk_size * vdsc_cfg->slice_height;

	while ((num_extra_mux_bits > 0) &&
	       ((slice_bits - num_extra_mux_bits) % vdsc_cfg->mux_word_size))
		num_extra_mux_bits--;

	if (groups_per_line < vdsc_cfg->initial_scale_value - 8)
		vdsc_cfg->initial_scale_value = groups_per_line + 8;

	/* scale_decrement_interval calculation according to DSC spec 1.11 */
	if (vdsc_cfg->initial_scale_value > 8)
		vdsc_cfg->scale_decrement_interval = groups_per_line /
			(vdsc_cfg->initial_scale_value - 8);
	else
		vdsc_cfg->scale_decrement_interval = DSC_SCALE_DECREMENT_INTERVAL_MAX;

	vdsc_cfg->final_offset = vdsc_cfg->rc_model_size -
		(vdsc_cfg->initial_xmit_delay *
		 vdsc_cfg->bits_per_pixel + 8) / 16 + num_extra_mux_bits;

	if (vdsc_cfg->final_offset >= vdsc_cfg->rc_model_size) {
		DRM_DEBUG_KMS("FinalOfs < RcModelSze for this InitialXmitDelay\n");
		return -ERANGE;
	}

	final_scale = (vdsc_cfg->rc_model_size * 8) /
		(vdsc_cfg->rc_model_size - vdsc_cfg->final_offset);
	if (vdsc_cfg->slice_height > 1)
		/*
		 * NflBpgOffset is 16 bit value with 11 fractional bits
		 * hence we multiply by 2^11 for preserving the
		 * fractional part
		 */
		vdsc_cfg->nfl_bpg_offset = DIV_ROUND_UP((vdsc_cfg->first_line_bpg_offset << 11),
							(vdsc_cfg->slice_height - 1));
	else
		vdsc_cfg->nfl_bpg_offset = 0;

	/* 2^16 - 1 */
	if (vdsc_cfg->nfl_bpg_offset > 65535) {
		DRM_DEBUG_KMS("NflBpgOffset is too large for this slice height\n");
		return -ERANGE;
	}

	/* Number of groups used to code the entire slice */
	groups_total = groups_per_line * vdsc_cfg->slice_height;

	/* slice_bpg_offset is 16 bit value with 11 fractional bits */
	vdsc_cfg->slice_bpg_offset = DIV_ROUND_UP(((vdsc_cfg->rc_model_size -
						    vdsc_cfg->initial_offset +
						    num_extra_mux_bits) << 11),
						  groups_total);

	if (final_scale > 9) {
		/*
		 * ScaleIncrementInterval =
		 * finaloffset/((NflBpgOffset + SliceBpgOffset)*8(finalscale - 1.125))
		 * as (NflBpgOffset + SliceBpgOffset) has 11 bit fractional value,
		 * we need divide by 2^11 from pstDscCfg values
		 */
		vdsc_cfg->scale_increment_interval =
				(vdsc_cfg->final_offset * (1 << 11)) /
				((vdsc_cfg->nfl_bpg_offset +
				vdsc_cfg->slice_bpg_offset) *
				(final_scale - 9));
	} else {
		/*
		 * If finalScaleValue is less than or equal to 9, a value of 0 should
		 * be used to disable the scale increment at the end of the slice
		 */
		vdsc_cfg->scale_increment_interval = 0;
	}

	if (vdsc_cfg->scale_increment_interval > 65535) {
		DRM_DEBUG_KMS("ScaleIncrementInterval is large for slice height\n");
		return -ERANGE;
	}

	/*
	 * DSC spec mentions that bits_per_pixel specifies the target
	 * bits/pixel (bpp) rate that is used by the encoder,
	 * in steps of 1/16 of a bit per pixel
	 */
	rbs_min = vdsc_cfg->rc_model_size - vdsc_cfg->initial_offset +
		DIV_ROUND_UP(vdsc_cfg->initial_xmit_delay *
			     vdsc_cfg->bits_per_pixel, 16) +
		groups_per_line * vdsc_cfg->first_line_bpg_offset;

	hrd_delay = DIV_ROUND_UP((rbs_min * 16), vdsc_cfg->bits_per_pixel);
	vdsc_cfg->rc_bits = (hrd_delay * vdsc_cfg->bits_per_pixel) / 16;
	vdsc_cfg->initial_dec_delay = hrd_delay - vdsc_cfg->initial_xmit_delay;

	return 0;
}