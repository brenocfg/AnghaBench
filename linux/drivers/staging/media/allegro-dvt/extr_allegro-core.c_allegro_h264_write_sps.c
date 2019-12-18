#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bit_rate_scale; int cpb_size_scale; int* bit_rate_value_minus1; int* cpb_size_value_minus1; int* cbr_flag; int initial_cpb_removal_delay_length_minus1; int cpb_removal_delay_length_minus1; int dpb_output_delay_length_minus1; scalar_t__ time_offset_length; scalar_t__ cpb_cnt_minus1; } ;
struct TYPE_6__ {int video_signal_type_present_flag; int video_format; int colour_description_present_flag; int colour_primaries; int transfer_characteristics; int matrix_coefficients; int chroma_loc_info_present_flag; int timing_info_present_flag; int num_units_in_tick; int time_scale; int fixed_frame_rate_flag; int vcl_hrd_parameters_present_flag; int pic_struct_present_flag; scalar_t__ bitstream_restriction_flag; scalar_t__ low_delay_hrd_flag; TYPE_1__ vcl_hrd_parameters; scalar_t__ nal_hrd_parameters_present_flag; scalar_t__ chroma_sample_loc_type_bottom_field; scalar_t__ chroma_sample_loc_type_top_field; scalar_t__ video_full_range_flag; scalar_t__ overscan_info_present_flag; scalar_t__ aspect_ratio_info_present_flag; } ;
struct nal_h264_sps {int constraint_set1_flag; int log2_max_pic_order_cnt_lsb_minus4; int max_num_ref_frames; int frame_mbs_only_flag; int direct_8x8_inference_flag; int frame_cropping_flag; unsigned int crop_right; unsigned int crop_bottom; int vui_parameters_present_flag; TYPE_3__ vui; scalar_t__ crop_top; scalar_t__ crop_left; scalar_t__ mb_adaptive_frame_field_flag; void* pic_height_in_map_units_minus1; void* pic_width_in_mbs_minus1; scalar_t__ gaps_in_frame_num_value_allowed_flag; scalar_t__ pic_order_cnt_type; scalar_t__ log2_max_frame_num_minus4; scalar_t__ seq_parameter_set_id; int /*<<< orphan*/  level_idc; scalar_t__ constraint_set5_flag; scalar_t__ constraint_set4_flag; scalar_t__ constraint_set3_flag; scalar_t__ constraint_set2_flag; scalar_t__ constraint_set0_flag; int /*<<< orphan*/  profile_idc; } ;
struct allegro_dev {TYPE_2__* plat_dev; } ;
struct allegro_channel {unsigned int width; unsigned int height; int bitrate_peak; int cpb_size; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; struct allegro_dev* dev; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SIZE_MACROBLOCK ; 
 int /*<<< orphan*/  kfree (struct nal_h264_sps*) ; 
 struct nal_h264_sps* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nal_h264_level_from_v4l2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nal_h264_profile_from_v4l2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nal_h264_write_sps (int /*<<< orphan*/ *,void*,size_t,struct nal_h264_sps*) ; 
 unsigned int round_up (unsigned int,unsigned int) ; 

__attribute__((used)) static ssize_t allegro_h264_write_sps(struct allegro_channel *channel,
				      void *dest, size_t n)
{
	struct allegro_dev *dev = channel->dev;
	struct nal_h264_sps *sps;
	ssize_t size;
	unsigned int size_mb = SIZE_MACROBLOCK;
	/* Calculation of crop units in Rec. ITU-T H.264 (04/2017) p. 76 */
	unsigned int crop_unit_x = 2;
	unsigned int crop_unit_y = 2;

	sps = kzalloc(sizeof(*sps), GFP_KERNEL);
	if (!sps)
		return -ENOMEM;

	sps->profile_idc = nal_h264_profile_from_v4l2(channel->profile);
	sps->constraint_set0_flag = 0;
	sps->constraint_set1_flag = 1;
	sps->constraint_set2_flag = 0;
	sps->constraint_set3_flag = 0;
	sps->constraint_set4_flag = 0;
	sps->constraint_set5_flag = 0;
	sps->level_idc = nal_h264_level_from_v4l2(channel->level);
	sps->seq_parameter_set_id = 0;
	sps->log2_max_frame_num_minus4 = 0;
	sps->pic_order_cnt_type = 0;
	sps->log2_max_pic_order_cnt_lsb_minus4 = 6;
	sps->max_num_ref_frames = 3;
	sps->gaps_in_frame_num_value_allowed_flag = 0;
	sps->pic_width_in_mbs_minus1 =
		DIV_ROUND_UP(channel->width, size_mb) - 1;
	sps->pic_height_in_map_units_minus1 =
		DIV_ROUND_UP(channel->height, size_mb) - 1;
	sps->frame_mbs_only_flag = 1;
	sps->mb_adaptive_frame_field_flag = 0;
	sps->direct_8x8_inference_flag = 1;
	sps->frame_cropping_flag =
		(channel->width % size_mb) || (channel->height % size_mb);
	if (sps->frame_cropping_flag) {
		sps->crop_left = 0;
		sps->crop_right = (round_up(channel->width, size_mb) - channel->width) / crop_unit_x;
		sps->crop_top = 0;
		sps->crop_bottom = (round_up(channel->height, size_mb) - channel->height) / crop_unit_y;
	}
	sps->vui_parameters_present_flag = 1;
	sps->vui.aspect_ratio_info_present_flag = 0;
	sps->vui.overscan_info_present_flag = 0;
	sps->vui.video_signal_type_present_flag = 1;
	sps->vui.video_format = 1;
	sps->vui.video_full_range_flag = 0;
	sps->vui.colour_description_present_flag = 1;
	sps->vui.colour_primaries = 5;
	sps->vui.transfer_characteristics = 5;
	sps->vui.matrix_coefficients = 5;
	sps->vui.chroma_loc_info_present_flag = 1;
	sps->vui.chroma_sample_loc_type_top_field = 0;
	sps->vui.chroma_sample_loc_type_bottom_field = 0;
	sps->vui.timing_info_present_flag = 1;
	sps->vui.num_units_in_tick = 1;
	sps->vui.time_scale = 50;
	sps->vui.fixed_frame_rate_flag = 1;
	sps->vui.nal_hrd_parameters_present_flag = 0;
	sps->vui.vcl_hrd_parameters_present_flag = 1;
	sps->vui.vcl_hrd_parameters.cpb_cnt_minus1 = 0;
	sps->vui.vcl_hrd_parameters.bit_rate_scale = 0;
	sps->vui.vcl_hrd_parameters.cpb_size_scale = 1;
	/* See Rec. ITU-T H.264 (04/2017) p. 410 E-53 */
	sps->vui.vcl_hrd_parameters.bit_rate_value_minus1[0] =
		channel->bitrate_peak / (1 << (6 + sps->vui.vcl_hrd_parameters.bit_rate_scale)) - 1;
	/* See Rec. ITU-T H.264 (04/2017) p. 410 E-54 */
	sps->vui.vcl_hrd_parameters.cpb_size_value_minus1[0] =
		(channel->cpb_size * 1000) / (1 << (4 + sps->vui.vcl_hrd_parameters.cpb_size_scale)) - 1;
	sps->vui.vcl_hrd_parameters.cbr_flag[0] = 1;
	sps->vui.vcl_hrd_parameters.initial_cpb_removal_delay_length_minus1 = 31;
	sps->vui.vcl_hrd_parameters.cpb_removal_delay_length_minus1 = 31;
	sps->vui.vcl_hrd_parameters.dpb_output_delay_length_minus1 = 31;
	sps->vui.vcl_hrd_parameters.time_offset_length = 0;
	sps->vui.low_delay_hrd_flag = 0;
	sps->vui.pic_struct_present_flag = 1;
	sps->vui.bitstream_restriction_flag = 0;

	size = nal_h264_write_sps(&dev->plat_dev->dev, dest, n, sps);

	kfree(sps);

	return size;
}