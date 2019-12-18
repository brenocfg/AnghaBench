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
struct vb2_v4l2_buffer {int dummy; } ;
struct delta_frame {int /*<<< orphan*/  index; int /*<<< orphan*/  state; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct delta_ctx {int /*<<< orphan*/  name; TYPE_1__ fh; struct delta_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_FRAME_FREE ; 
 int /*<<< orphan*/  DELTA_FRAME_M2M ; 
 int EIO ; 
 int ENODATA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dump_frames_status (struct delta_ctx*) ; 
 struct delta_frame* to_frame (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 

int delta_get_free_frame(struct delta_ctx *ctx,
			 struct delta_frame **pframe)
{
	struct delta_dev *delta = ctx->dev;
	struct vb2_v4l2_buffer *vbuf;
	struct delta_frame *frame;

	*pframe = NULL;

	vbuf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
	if (!vbuf) {
		dev_err(delta->dev, "%s no frame available",
			ctx->name);
		return -EIO;
	}

	frame = to_frame(vbuf);
	frame->state &= ~DELTA_FRAME_M2M;
	if (frame->state != DELTA_FRAME_FREE) {
		dev_err(delta->dev,
			"%s frame[%d] is not free\n",
			ctx->name, frame->index);
		dump_frames_status(ctx);
		return -ENODATA;
	}

	dev_dbg(delta->dev,
		"%s get free frame[%d]\n", ctx->name, frame->index);

	*pframe = frame;
	return 0;
}