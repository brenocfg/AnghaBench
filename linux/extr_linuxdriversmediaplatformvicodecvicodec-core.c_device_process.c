#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct vicodec_q_data {int width; int height; int /*<<< orphan*/  sequence; } ;
struct vicodec_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct vicodec_ctx {scalar_t__ is_enc; int /*<<< orphan*/ * compressed_frame; struct vicodec_dev* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int flags; int /*<<< orphan*/  field; int /*<<< orphan*/  timecode; TYPE_1__ vb2_buf; scalar_t__ sequence; } ;
struct cframe_hdr {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EFAULT ; 
 int V4L2_BUF_FLAG_BFRAME ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int V4L2_BUF_FLAG_LAST ; 
 int V4L2_BUF_FLAG_PFRAME ; 
 int V4L2_BUF_FLAG_TIMECODE ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int decode (struct vicodec_ctx*,struct vicodec_q_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode (struct vicodec_ctx*,struct vicodec_q_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vicodec_q_data* get_q_data (struct vicodec_ctx*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * vb2_plane_vaddr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int device_process(struct vicodec_ctx *ctx,
			  struct vb2_v4l2_buffer *in_vb,
			  struct vb2_v4l2_buffer *out_vb)
{
	struct vicodec_dev *dev = ctx->dev;
	struct vicodec_q_data *q_out, *q_cap;
	u8 *p_in, *p_out;
	int ret;

	q_out = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	q_cap = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	if (ctx->is_enc)
		p_in = vb2_plane_vaddr(&in_vb->vb2_buf, 0);
	else
		p_in = ctx->compressed_frame;
	p_out = vb2_plane_vaddr(&out_vb->vb2_buf, 0);
	if (!p_in || !p_out) {
		v4l2_err(&dev->v4l2_dev,
			 "Acquiring kernel pointers to buffers failed\n");
		return -EFAULT;
	}

	if (ctx->is_enc) {
		struct cframe_hdr *p_hdr = (struct cframe_hdr *)p_out;

		encode(ctx, q_out, p_in, p_out);
		vb2_set_plane_payload(&out_vb->vb2_buf, 0,
				      sizeof(*p_hdr) + ntohl(p_hdr->size));
	} else {
		ret = decode(ctx, q_cap, p_in, p_out);
		if (ret)
			return ret;
		vb2_set_plane_payload(&out_vb->vb2_buf, 0,
				      q_cap->width * q_cap->height * 3 / 2);
	}

	out_vb->sequence = q_cap->sequence++;
	out_vb->vb2_buf.timestamp = in_vb->vb2_buf.timestamp;

	if (in_vb->flags & V4L2_BUF_FLAG_TIMECODE)
		out_vb->timecode = in_vb->timecode;
	out_vb->field = in_vb->field;
	out_vb->flags &= ~V4L2_BUF_FLAG_LAST;
	out_vb->flags |= in_vb->flags &
		(V4L2_BUF_FLAG_TIMECODE |
		 V4L2_BUF_FLAG_KEYFRAME |
		 V4L2_BUF_FLAG_PFRAME |
		 V4L2_BUF_FLAG_BFRAME |
		 V4L2_BUF_FLAG_TSTAMP_SRC_MASK);

	return 0;
}