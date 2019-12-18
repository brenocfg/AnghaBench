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
struct nal_h264_pps {scalar_t__ pic_parameter_set_id; scalar_t__ seq_parameter_set_id; scalar_t__ num_slice_groups_minus1; scalar_t__ slice_group_map_type; scalar_t__* run_length_minus1; scalar_t__* top_left; scalar_t__* bottom_right; scalar_t__ slice_group_change_rate_minus1; scalar_t__ pic_size_in_map_units_minus1; scalar_t__ num_ref_idx_l0_default_active_minus1; scalar_t__ num_ref_idx_l1_default_active_minus1; int /*<<< orphan*/  second_chroma_qp_index_offset; scalar_t__ pic_scaling_matrix_present_flag; scalar_t__ transform_8x8_mode_flag; scalar_t__ redundant_pic_cnt_present_flag; scalar_t__ constrained_intra_pred_flag; scalar_t__ deblocking_filter_control_present_flag; int /*<<< orphan*/  chroma_qp_index_offset; int /*<<< orphan*/  pic_init_qs_minus26; int /*<<< orphan*/  pic_init_qp_minus26; int /*<<< orphan*/  weighted_bipred_idc; scalar_t__ weighted_pred_flag; int /*<<< orphan*/ * slice_group_id; scalar_t__ slice_group_change_direction_flag; scalar_t__ bottom_field_pic_order_in_frame_present_flag; scalar_t__ entropy_coding_mode_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int order_base_2 (int) ; 
 int /*<<< orphan*/  rbsp_bit (struct rbsp*,scalar_t__*) ; 
 int /*<<< orphan*/  rbsp_bits (struct rbsp*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbsp_sev (struct rbsp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbsp_uev (struct rbsp*,scalar_t__*) ; 

__attribute__((used)) static void nal_h264_rbsp_pps(struct rbsp *rbsp, struct nal_h264_pps *pps)
{
	int i;

	rbsp_uev(rbsp, &pps->pic_parameter_set_id);
	rbsp_uev(rbsp, &pps->seq_parameter_set_id);
	rbsp_bit(rbsp, &pps->entropy_coding_mode_flag);
	rbsp_bit(rbsp, &pps->bottom_field_pic_order_in_frame_present_flag);
	rbsp_uev(rbsp, &pps->num_slice_groups_minus1);
	if (pps->num_slice_groups_minus1 > 0) {
		rbsp_uev(rbsp, &pps->slice_group_map_type);
		switch (pps->slice_group_map_type) {
		case 0:
			for (i = 0; i < pps->num_slice_groups_minus1; i++)
				rbsp_uev(rbsp, &pps->run_length_minus1[i]);
			break;
		case 2:
			for (i = 0; i < pps->num_slice_groups_minus1; i++) {
				rbsp_uev(rbsp, &pps->top_left[i]);
				rbsp_uev(rbsp, &pps->bottom_right[i]);
			}
			break;
		case 3: case 4: case 5:
			rbsp_bit(rbsp, &pps->slice_group_change_direction_flag);
			rbsp_uev(rbsp, &pps->slice_group_change_rate_minus1);
			break;
		case 6:
			rbsp_uev(rbsp, &pps->pic_size_in_map_units_minus1);
			for (i = 0; i < pps->pic_size_in_map_units_minus1; i++)
				rbsp_bits(rbsp,
					  order_base_2(pps->num_slice_groups_minus1 + 1),
					  &pps->slice_group_id[i]);
			break;
		default:
			break;
		}
	}
	rbsp_uev(rbsp, &pps->num_ref_idx_l0_default_active_minus1);
	rbsp_uev(rbsp, &pps->num_ref_idx_l1_default_active_minus1);
	rbsp_bit(rbsp, &pps->weighted_pred_flag);
	rbsp_bits(rbsp, 2, &pps->weighted_bipred_idc);
	rbsp_sev(rbsp, &pps->pic_init_qp_minus26);
	rbsp_sev(rbsp, &pps->pic_init_qs_minus26);
	rbsp_sev(rbsp, &pps->chroma_qp_index_offset);
	rbsp_bit(rbsp, &pps->deblocking_filter_control_present_flag);
	rbsp_bit(rbsp, &pps->constrained_intra_pred_flag);
	rbsp_bit(rbsp, &pps->redundant_pic_cnt_present_flag);
	if (/* more_rbsp_data() */ false) {
		rbsp_bit(rbsp, &pps->transform_8x8_mode_flag);
		rbsp_bit(rbsp, &pps->pic_scaling_matrix_present_flag);
		if (pps->pic_scaling_matrix_present_flag)
			rbsp->error = -EINVAL;
		rbsp_sev(rbsp, &pps->second_chroma_qp_index_offset);
	}
}