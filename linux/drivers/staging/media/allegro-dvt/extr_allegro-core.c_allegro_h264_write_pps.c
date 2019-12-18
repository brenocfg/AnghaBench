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
struct nal_h264_pps {int num_ref_idx_l0_default_active_minus1; int num_ref_idx_l1_default_active_minus1; int deblocking_filter_control_present_flag; scalar_t__ second_chroma_qp_index_offset; scalar_t__ pic_scaling_matrix_present_flag; scalar_t__ transform_8x8_mode_flag; scalar_t__ redundant_pic_cnt_present_flag; scalar_t__ constrained_intra_pred_flag; scalar_t__ chroma_qp_index_offset; scalar_t__ pic_init_qs_minus26; scalar_t__ pic_init_qp_minus26; scalar_t__ weighted_bipred_idc; scalar_t__ weighted_pred_flag; scalar_t__ num_slice_groups_minus1; scalar_t__ bottom_field_pic_order_in_frame_present_flag; scalar_t__ entropy_coding_mode_flag; scalar_t__ seq_parameter_set_id; scalar_t__ pic_parameter_set_id; } ;
struct allegro_dev {TYPE_1__* plat_dev; } ;
struct allegro_channel {struct allegro_dev* dev; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct nal_h264_pps*) ; 
 struct nal_h264_pps* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nal_h264_write_pps (int /*<<< orphan*/ *,void*,size_t,struct nal_h264_pps*) ; 

__attribute__((used)) static ssize_t allegro_h264_write_pps(struct allegro_channel *channel,
				      void *dest, size_t n)
{
	struct allegro_dev *dev = channel->dev;
	struct nal_h264_pps *pps;
	ssize_t size;

	pps = kzalloc(sizeof(*pps), GFP_KERNEL);
	if (!pps)
		return -ENOMEM;

	pps->pic_parameter_set_id = 0;
	pps->seq_parameter_set_id = 0;
	pps->entropy_coding_mode_flag = 0;
	pps->bottom_field_pic_order_in_frame_present_flag = 0;
	pps->num_slice_groups_minus1 = 0;
	pps->num_ref_idx_l0_default_active_minus1 = 2;
	pps->num_ref_idx_l1_default_active_minus1 = 2;
	pps->weighted_pred_flag = 0;
	pps->weighted_bipred_idc = 0;
	pps->pic_init_qp_minus26 = 0;
	pps->pic_init_qs_minus26 = 0;
	pps->chroma_qp_index_offset = 0;
	pps->deblocking_filter_control_present_flag = 1;
	pps->constrained_intra_pred_flag = 0;
	pps->redundant_pic_cnt_present_flag = 0;
	pps->transform_8x8_mode_flag = 0;
	pps->pic_scaling_matrix_present_flag = 0;
	pps->second_chroma_qp_index_offset = 0;

	size = nal_h264_write_pps(&dev->plat_dev->dev, dest, n, pps);

	kfree(pps);

	return size;
}