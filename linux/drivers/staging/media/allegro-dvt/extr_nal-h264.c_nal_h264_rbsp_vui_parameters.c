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
struct rbsp {int /*<<< orphan*/  error; } ;
struct nal_h264_vui_parameters {int aspect_ratio_idc; int sar_width; int sar_height; int video_format; int colour_primaries; int transfer_characteristics; int matrix_coefficients; int num_units_in_tick; int time_scale; int /*<<< orphan*/  max_dec_frame_buffering; int /*<<< orphan*/  max_num_reorder_frames; int /*<<< orphan*/  log21_max_mv_length_vertical; int /*<<< orphan*/  log2_max_mv_length_horizontal; int /*<<< orphan*/  max_bits_per_mb_denom; int /*<<< orphan*/  max_bytes_per_pic_denom; scalar_t__ motion_vectors_over_pic_boundaries_flag; scalar_t__ bitstream_restriction_flag; scalar_t__ pic_struct_present_flag; scalar_t__ low_delay_hrd_flag; scalar_t__ vcl_hrd_parameters_present_flag; scalar_t__ nal_hrd_parameters_present_flag; int /*<<< orphan*/  vcl_hrd_parameters; int /*<<< orphan*/  nal_hrd_parameters; scalar_t__ fixed_frame_rate_flag; scalar_t__ timing_info_present_flag; int /*<<< orphan*/  chroma_sample_loc_type_bottom_field; int /*<<< orphan*/  chroma_sample_loc_type_top_field; scalar_t__ chroma_loc_info_present_flag; scalar_t__ colour_description_present_flag; scalar_t__ video_full_range_flag; scalar_t__ video_signal_type_present_flag; scalar_t__ overscan_appropriate_flag; scalar_t__ overscan_info_present_flag; scalar_t__ aspect_ratio_info_present_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  nal_h264_rbsp_hrd_parameters (struct rbsp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbsp_bit (struct rbsp*,scalar_t__*) ; 
 int /*<<< orphan*/  rbsp_bits (struct rbsp*,int,int*) ; 
 int /*<<< orphan*/  rbsp_uev (struct rbsp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nal_h264_rbsp_vui_parameters(struct rbsp *rbsp,
					 struct nal_h264_vui_parameters *vui)
{
	if (!vui) {
		rbsp->error = -EINVAL;
		return;
	}

	rbsp_bit(rbsp, &vui->aspect_ratio_info_present_flag);
	if (vui->aspect_ratio_info_present_flag) {
		rbsp_bits(rbsp, 8, &vui->aspect_ratio_idc);
		if (vui->aspect_ratio_idc == 255) {
			rbsp_bits(rbsp, 16, &vui->sar_width);
			rbsp_bits(rbsp, 16, &vui->sar_height);
		}
	}

	rbsp_bit(rbsp, &vui->overscan_info_present_flag);
	if (vui->overscan_info_present_flag)
		rbsp_bit(rbsp, &vui->overscan_appropriate_flag);

	rbsp_bit(rbsp, &vui->video_signal_type_present_flag);
	if (vui->video_signal_type_present_flag) {
		rbsp_bits(rbsp, 3, &vui->video_format);
		rbsp_bit(rbsp, &vui->video_full_range_flag);

		rbsp_bit(rbsp, &vui->colour_description_present_flag);
		if (vui->colour_description_present_flag) {
			rbsp_bits(rbsp, 8, &vui->colour_primaries);
			rbsp_bits(rbsp, 8, &vui->transfer_characteristics);
			rbsp_bits(rbsp, 8, &vui->matrix_coefficients);
		}
	}

	rbsp_bit(rbsp, &vui->chroma_loc_info_present_flag);
	if (vui->chroma_loc_info_present_flag) {
		rbsp_uev(rbsp, &vui->chroma_sample_loc_type_top_field);
		rbsp_uev(rbsp, &vui->chroma_sample_loc_type_bottom_field);
	}

	rbsp_bit(rbsp, &vui->timing_info_present_flag);
	if (vui->timing_info_present_flag) {
		rbsp_bits(rbsp, 32, &vui->num_units_in_tick);
		rbsp_bits(rbsp, 32, &vui->time_scale);
		rbsp_bit(rbsp, &vui->fixed_frame_rate_flag);
	}

	rbsp_bit(rbsp, &vui->nal_hrd_parameters_present_flag);
	if (vui->nal_hrd_parameters_present_flag)
		nal_h264_rbsp_hrd_parameters(rbsp, &vui->nal_hrd_parameters);

	rbsp_bit(rbsp, &vui->vcl_hrd_parameters_present_flag);
	if (vui->vcl_hrd_parameters_present_flag)
		nal_h264_rbsp_hrd_parameters(rbsp, &vui->vcl_hrd_parameters);

	if (vui->nal_hrd_parameters_present_flag ||
	    vui->vcl_hrd_parameters_present_flag)
		rbsp_bit(rbsp, &vui->low_delay_hrd_flag);

	rbsp_bit(rbsp, &vui->pic_struct_present_flag);

	rbsp_bit(rbsp, &vui->bitstream_restriction_flag);
	if (vui->bitstream_restriction_flag) {
		rbsp_bit(rbsp, &vui->motion_vectors_over_pic_boundaries_flag);
		rbsp_uev(rbsp, &vui->max_bytes_per_pic_denom);
		rbsp_uev(rbsp, &vui->max_bits_per_mb_denom);
		rbsp_uev(rbsp, &vui->log2_max_mv_length_horizontal);
		rbsp_uev(rbsp, &vui->log21_max_mv_length_vertical);
		rbsp_uev(rbsp, &vui->max_num_reorder_frames);
		rbsp_uev(rbsp, &vui->max_dec_frame_buffering);
	}
}