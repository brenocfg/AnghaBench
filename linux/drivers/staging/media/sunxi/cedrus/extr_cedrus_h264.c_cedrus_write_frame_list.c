#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int /*<<< orphan*/ ** bufs; } ;
struct v4l2_h264_dpb_entry {int flags; int /*<<< orphan*/  bottom_field_order_cnt; int /*<<< orphan*/  top_field_order_cnt; int /*<<< orphan*/  reference_ts; } ;
struct v4l2_ctrl_h264_sps {int flags; } ;
struct v4l2_ctrl_h264_slice_params {int flags; } ;
struct v4l2_ctrl_h264_decode_params {int /*<<< orphan*/  bottom_field_order_cnt; int /*<<< orphan*/  top_field_order_cnt; struct v4l2_h264_dpb_entry* dpb; } ;
struct TYPE_8__ {struct v4l2_ctrl_h264_sps* sps; struct v4l2_ctrl_h264_slice_params* slice_params; struct v4l2_ctrl_h264_decode_params* decode_params; } ;
struct cedrus_run {TYPE_5__* dst; TYPE_1__ h264; } ;
struct cedrus_h264_sram_ref_pic {int dummy; } ;
struct cedrus_dev {int dummy; } ;
struct TYPE_11__ {TYPE_3__* m2m_ctx; } ;
struct cedrus_ctx {struct cedrus_dev* dev; TYPE_4__ fh; } ;
struct TYPE_13__ {unsigned int position; int /*<<< orphan*/  pic_type; } ;
struct TYPE_14__ {TYPE_6__ h264; } ;
struct cedrus_buffer {TYPE_7__ codec; } ;
typedef  int /*<<< orphan*/  pic_list ;
struct TYPE_12__ {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_9__ {struct vb2_queue q; } ;
struct TYPE_10__ {TYPE_2__ cap_q_ctx; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct v4l2_h264_dpb_entry*) ; 
 unsigned long BIT (unsigned int) ; 
 int CEDRUS_H264_FRAME_NUM ; 
 int /*<<< orphan*/  CEDRUS_H264_PIC_TYPE_FIELD ; 
 int /*<<< orphan*/  CEDRUS_H264_PIC_TYPE_FRAME ; 
 int /*<<< orphan*/  CEDRUS_H264_PIC_TYPE_MBAFF ; 
 int /*<<< orphan*/  CEDRUS_SRAM_H264_FRAMEBUFFER_LIST ; 
 int V4L2_H264_DPB_ENTRY_FLAG_ACTIVE ; 
 int V4L2_H264_DPB_ENTRY_FLAG_VALID ; 
 int V4L2_H264_SLICE_FLAG_FIELD_PIC ; 
 int V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD ; 
 int /*<<< orphan*/  VE_H264_OUTPUT_FRAME_IDX ; 
 int /*<<< orphan*/  cedrus_fill_ref_pic (struct cedrus_ctx*,struct cedrus_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cedrus_h264_sram_ref_pic*) ; 
 int /*<<< orphan*/  cedrus_h264_write_sram (struct cedrus_dev*,int /*<<< orphan*/ ,struct cedrus_h264_sram_ref_pic*,int) ; 
 int /*<<< orphan*/  cedrus_write (struct cedrus_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int find_first_zero_bit (unsigned long*,int) ; 
 unsigned int find_next_zero_bit (unsigned long*,int,unsigned int) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (struct cedrus_h264_sram_ref_pic*,int /*<<< orphan*/ ,int) ; 
 int vb2_find_timestamp (struct vb2_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cedrus_buffer* vb2_to_cedrus_buffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cedrus_write_frame_list(struct cedrus_ctx *ctx,
				    struct cedrus_run *run)
{
	struct cedrus_h264_sram_ref_pic pic_list[CEDRUS_H264_FRAME_NUM];
	const struct v4l2_ctrl_h264_decode_params *decode = run->h264.decode_params;
	const struct v4l2_ctrl_h264_slice_params *slice = run->h264.slice_params;
	const struct v4l2_ctrl_h264_sps *sps = run->h264.sps;
	struct vb2_queue *cap_q = &ctx->fh.m2m_ctx->cap_q_ctx.q;
	struct cedrus_buffer *output_buf;
	struct cedrus_dev *dev = ctx->dev;
	unsigned long used_dpbs = 0;
	unsigned int position;
	unsigned int output = 0;
	unsigned int i;

	memset(pic_list, 0, sizeof(pic_list));

	for (i = 0; i < ARRAY_SIZE(decode->dpb); i++) {
		const struct v4l2_h264_dpb_entry *dpb = &decode->dpb[i];
		struct cedrus_buffer *cedrus_buf;
		int buf_idx;

		if (!(dpb->flags & V4L2_H264_DPB_ENTRY_FLAG_VALID))
			continue;

		buf_idx = vb2_find_timestamp(cap_q, dpb->reference_ts, 0);
		if (buf_idx < 0)
			continue;

		cedrus_buf = vb2_to_cedrus_buffer(cap_q->bufs[buf_idx]);
		position = cedrus_buf->codec.h264.position;
		used_dpbs |= BIT(position);

		if (!(dpb->flags & V4L2_H264_DPB_ENTRY_FLAG_ACTIVE))
			continue;

		cedrus_fill_ref_pic(ctx, cedrus_buf,
				    dpb->top_field_order_cnt,
				    dpb->bottom_field_order_cnt,
				    &pic_list[position]);

		output = max(position, output);
	}

	position = find_next_zero_bit(&used_dpbs, CEDRUS_H264_FRAME_NUM,
				      output);
	if (position >= CEDRUS_H264_FRAME_NUM)
		position = find_first_zero_bit(&used_dpbs, CEDRUS_H264_FRAME_NUM);

	output_buf = vb2_to_cedrus_buffer(&run->dst->vb2_buf);
	output_buf->codec.h264.position = position;

	if (slice->flags & V4L2_H264_SLICE_FLAG_FIELD_PIC)
		output_buf->codec.h264.pic_type = CEDRUS_H264_PIC_TYPE_FIELD;
	else if (sps->flags & V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD)
		output_buf->codec.h264.pic_type = CEDRUS_H264_PIC_TYPE_MBAFF;
	else
		output_buf->codec.h264.pic_type = CEDRUS_H264_PIC_TYPE_FRAME;

	cedrus_fill_ref_pic(ctx, output_buf,
			    decode->top_field_order_cnt,
			    decode->bottom_field_order_cnt,
			    &pic_list[position]);

	cedrus_h264_write_sram(dev, CEDRUS_SRAM_H264_FRAMEBUFFER_LIST,
			       pic_list, sizeof(pic_list));

	cedrus_write(dev, VE_H264_OUTPUT_FRAME_IDX, position);
}