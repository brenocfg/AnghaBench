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
struct hantro_ctx {int /*<<< orphan*/  dst_fmt; int /*<<< orphan*/  vpu_dst_fmt; int /*<<< orphan*/  src_fmt; int /*<<< orphan*/  vpu_src_fmt; } ;

/* Variables and functions */
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int hantro_buf_plane_check (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hantro_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int hantro_buf_prepare(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
	struct hantro_ctx *ctx = vb2_get_drv_priv(vq);

	if (V4L2_TYPE_IS_OUTPUT(vq->type))
		return hantro_buf_plane_check(vb, ctx->vpu_src_fmt,
						  &ctx->src_fmt);

	return hantro_buf_plane_check(vb, ctx->vpu_dst_fmt, &ctx->dst_fmt);
}