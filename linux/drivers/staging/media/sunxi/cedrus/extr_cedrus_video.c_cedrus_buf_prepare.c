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
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct vb2_buffer {struct vb2_queue* vb2_queue; } ;
struct v4l2_pix_format {scalar_t__ sizeimage; } ;
struct cedrus_ctx {struct v4l2_pix_format dst_fmt; struct v4l2_pix_format src_fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 struct cedrus_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cedrus_buf_prepare(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
	struct cedrus_ctx *ctx = vb2_get_drv_priv(vq);
	struct v4l2_pix_format *pix_fmt;

	if (V4L2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->src_fmt;
	else
		pix_fmt = &ctx->dst_fmt;

	if (vb2_plane_size(vb, 0) < pix_fmt->sizeimage)
		return -EINVAL;

	vb2_set_plane_payload(vb, 0, pix_fmt->sizeimage);

	return 0;
}