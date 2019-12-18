#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int flags; int /*<<< orphan*/  timecode; TYPE_1__ vb2_buf; } ;
struct deinterlace_dev {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  busy; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct deinterlace_ctx {TYPE_2__ fh; struct deinterlace_dev* dev; } ;

/* Variables and functions */
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (struct deinterlace_dev*,char*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_callback(void *data)
{
	struct deinterlace_ctx *curr_ctx = data;
	struct deinterlace_dev *pcdev = curr_ctx->dev;
	struct vb2_v4l2_buffer *src_vb, *dst_vb;

	atomic_set(&pcdev->busy, 0);

	src_vb = v4l2_m2m_src_buf_remove(curr_ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_remove(curr_ctx->fh.m2m_ctx);

	dst_vb->vb2_buf.timestamp = src_vb->vb2_buf.timestamp;
	dst_vb->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst_vb->flags |=
		src_vb->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst_vb->timecode = src_vb->timecode;

	v4l2_m2m_buf_done(src_vb, VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_done(dst_vb, VB2_BUF_STATE_DONE);

	v4l2_m2m_job_finish(pcdev->m2m_dev, curr_ctx->fh.m2m_ctx);

	dprintk(pcdev, "dma transfers completed.\n");
}