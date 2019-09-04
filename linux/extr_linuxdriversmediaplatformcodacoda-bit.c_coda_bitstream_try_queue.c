#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_4__ {scalar_t__ size; } ;
struct coda_ctx {scalar_t__ qsequence; int hold; TYPE_3__* dev; TYPE_2__* codec; TYPE_1__ bitstream; } ;
struct TYPE_6__ {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_5__ {scalar_t__ src_fourcc; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_H264 ; 
 int /*<<< orphan*/  coda_bitstream_pad (struct coda_ctx*,int) ; 
 int coda_bitstream_queue (struct coda_ctx*,struct vb2_v4l2_buffer*) ; 
 scalar_t__ coda_get_bitstream_payload (struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_kfifo_sync_to_device_write (struct coda_ctx*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct coda_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 unsigned long vb2_get_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool coda_bitstream_try_queue(struct coda_ctx *ctx,
				     struct vb2_v4l2_buffer *src_buf)
{
	unsigned long payload = vb2_get_plane_payload(&src_buf->vb2_buf, 0);
	int ret;

	if (coda_get_bitstream_payload(ctx) + payload + 512 >=
	    ctx->bitstream.size)
		return false;

	if (vb2_plane_vaddr(&src_buf->vb2_buf, 0) == NULL) {
		v4l2_err(&ctx->dev->v4l2_dev, "trying to queue empty buffer\n");
		return true;
	}

	/* Add zero padding before the first H.264 buffer, if it is too small */
	if (ctx->qsequence == 0 && payload < 512 &&
	    ctx->codec->src_fourcc == V4L2_PIX_FMT_H264)
		coda_bitstream_pad(ctx, 512 - payload);

	ret = coda_bitstream_queue(ctx, src_buf);
	if (ret < 0) {
		v4l2_err(&ctx->dev->v4l2_dev, "bitstream buffer overflow\n");
		return false;
	}
	/* Sync read pointer to device */
	if (ctx == v4l2_m2m_get_curr_priv(ctx->dev->m2m_dev))
		coda_kfifo_sync_to_device_write(ctx);

	ctx->hold = false;

	return true;
}