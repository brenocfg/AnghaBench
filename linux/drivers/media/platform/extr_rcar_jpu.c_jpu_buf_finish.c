#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct vb2_v4l2_buffer {scalar_t__ sequence; } ;
struct vb2_buffer {scalar_t__ state; TYPE_3__* vb2_queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct jpu_q_data {TYPE_2__* fmtinfo; TYPE_1__ format; } ;
struct jpu_ctx {int /*<<< orphan*/  encoder; struct jpu_q_data out_q; } ;
struct jpu_buffer {size_t compr_quality; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_8__ {int /*<<< orphan*/  sequence; } ;
struct TYPE_7__ {int type; } ;
struct TYPE_6__ {int /*<<< orphan*/  subsampling; } ;

/* Variables and functions */
 int /*<<< orphan*/  JPU_JPEG_HDR_SIZE ; 
 int JPU_JPEG_HEIGHT_OFFSET ; 
 int JPU_JPEG_SUBS_OFFSET ; 
 int JPU_JPEG_WIDTH_OFFSET ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int) ; 
 scalar_t__ VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jpeg_hdrs ; 
 TYPE_4__* jpu_get_q_data (struct jpu_ctx*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct jpu_ctx* vb2_get_drv_priv (TYPE_3__*) ; 
 int /*<<< orphan*/ * vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct jpu_buffer* vb2_to_jpu_buffer (struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static void jpu_buf_finish(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct jpu_buffer *jpu_buf = vb2_to_jpu_buffer(vbuf);
	struct jpu_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct jpu_q_data *q_data = &ctx->out_q;
	enum v4l2_buf_type type = vb->vb2_queue->type;
	u8 *buffer;

	if (vb->state == VB2_BUF_STATE_DONE)
		vbuf->sequence = jpu_get_q_data(ctx, type)->sequence++;

	if (!ctx->encoder || vb->state != VB2_BUF_STATE_DONE ||
	    V4L2_TYPE_IS_OUTPUT(type))
		return;

	buffer = vb2_plane_vaddr(vb, 0);

	memcpy(buffer, jpeg_hdrs[jpu_buf->compr_quality], JPU_JPEG_HDR_SIZE);
	*(__be16 *)(buffer + JPU_JPEG_HEIGHT_OFFSET) =
					cpu_to_be16(q_data->format.height);
	*(__be16 *)(buffer + JPU_JPEG_WIDTH_OFFSET) =
					cpu_to_be16(q_data->format.width);
	*(buffer + JPU_JPEG_SUBS_OFFSET) = q_data->fmtinfo->subsampling;
}