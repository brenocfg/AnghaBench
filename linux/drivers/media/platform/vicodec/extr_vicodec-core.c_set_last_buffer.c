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
struct vicodec_q_data {int /*<<< orphan*/  sequence; } ;
struct vicodec_ctx {int /*<<< orphan*/  is_enc; } ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  flags; scalar_t__ sequence; int /*<<< orphan*/  vb2_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_LAST ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 struct vicodec_q_data* get_q_data (struct vicodec_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_copy_metadata (struct vb2_v4l2_buffer const*,struct vb2_v4l2_buffer*,int) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_last_buffer(struct vb2_v4l2_buffer *dst_buf,
			    const struct vb2_v4l2_buffer *src_buf,
			    struct vicodec_ctx *ctx)
{
	struct vicodec_q_data *q_dst = get_q_data(ctx,
						  V4L2_BUF_TYPE_VIDEO_CAPTURE);

	vb2_set_plane_payload(&dst_buf->vb2_buf, 0, 0);
	dst_buf->sequence = q_dst->sequence++;

	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, !ctx->is_enc);
	dst_buf->flags |= V4L2_BUF_FLAG_LAST;
	v4l2_m2m_buf_done(dst_buf, VB2_BUF_STATE_DONE);
}