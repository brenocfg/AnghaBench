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
struct vb2_queue {int buf_struct_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  min_buffers_needed; int /*<<< orphan*/  type; } ;
struct hva_stream {int dummy; } ;
struct hva_frame {int dummy; } ;
struct hva_ctx {TYPE_1__* hva_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIN_FRAMES ; 
 int /*<<< orphan*/  MIN_STREAMS ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int queue_init (struct hva_ctx*,struct vb2_queue*) ; 

__attribute__((used)) static int hva_queue_init(void *priv, struct vb2_queue *src_vq,
			  struct vb2_queue *dst_vq)
{
	struct hva_ctx *ctx = priv;
	int ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->buf_struct_size = sizeof(struct hva_frame);
	src_vq->min_buffers_needed = MIN_FRAMES;
	src_vq->dev = ctx->hva_dev->dev;

	ret = queue_init(ctx, src_vq);
	if (ret)
		return ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->buf_struct_size = sizeof(struct hva_stream);
	dst_vq->min_buffers_needed = MIN_STREAMS;
	dst_vq->dev = ctx->hva_dev->dev;

	return queue_init(ctx, dst_vq);
}