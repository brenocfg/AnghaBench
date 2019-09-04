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
struct vicodec_q_data {unsigned int width; unsigned int height; scalar_t__ sequence; } ;
struct TYPE_2__ {void* cb; void* cr; void* luma; scalar_t__ height; scalar_t__ width; } ;
struct vicodec_ctx {unsigned int comp_max_size; int comp_has_frame; scalar_t__ comp_magic_cnt; scalar_t__ comp_size; scalar_t__ cur_buf_offset; scalar_t__ gop_cnt; int /*<<< orphan*/  ctrl_gop_size; int /*<<< orphan*/  gop_size; int /*<<< orphan*/ * last_dst_buf; int /*<<< orphan*/ * last_src_buf; TYPE_1__ ref_frame; void* compressed_frame; } ;
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct cframe_hdr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 struct vicodec_q_data* get_q_data (struct vicodec_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 struct vicodec_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vicodec_return_bufs (struct vb2_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vicodec_start_streaming(struct vb2_queue *q,
				   unsigned int count)
{
	struct vicodec_ctx *ctx = vb2_get_drv_priv(q);
	struct vicodec_q_data *q_data = get_q_data(ctx, q->type);
	unsigned int size = q_data->width * q_data->height;

	q_data->sequence = 0;

	if (!V4L2_TYPE_IS_OUTPUT(q->type))
		return 0;

	ctx->ref_frame.width = ctx->ref_frame.height = 0;
	ctx->ref_frame.luma = kvmalloc(size * 3 / 2, GFP_KERNEL);
	ctx->comp_max_size = size * 3 / 2 + sizeof(struct cframe_hdr);
	ctx->compressed_frame = kvmalloc(ctx->comp_max_size, GFP_KERNEL);
	if (!ctx->ref_frame.luma || !ctx->compressed_frame) {
		kvfree(ctx->ref_frame.luma);
		kvfree(ctx->compressed_frame);
		vicodec_return_bufs(q, VB2_BUF_STATE_QUEUED);
		return -ENOMEM;
	}
	ctx->ref_frame.cb = ctx->ref_frame.luma + size;
	ctx->ref_frame.cr = ctx->ref_frame.cb + size / 4;
	ctx->last_src_buf = NULL;
	ctx->last_dst_buf = NULL;
	v4l2_ctrl_grab(ctx->ctrl_gop_size, true);
	ctx->gop_size = v4l2_ctrl_g_ctrl(ctx->ctrl_gop_size);
	ctx->gop_cnt = 0;
	ctx->cur_buf_offset = 0;
	ctx->comp_size = 0;
	ctx->comp_magic_cnt = 0;
	ctx->comp_has_frame = false;

	return 0;
}