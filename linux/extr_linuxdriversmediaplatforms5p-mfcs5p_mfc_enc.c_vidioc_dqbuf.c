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
struct v4l2_event {int /*<<< orphan*/  type; } ;
struct v4l2_buffer {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  done_list; } ;
struct s5p_mfc_ctx {scalar_t__ state; int /*<<< orphan*/  fh; TYPE_1__ vq_dst; TYPE_1__ vq_src; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ MFCINST_ERROR ; 
 scalar_t__ MFCINST_FINISHED ; 
 int O_NONBLOCK ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  V4L2_EVENT_EOS ; 
 struct s5p_mfc_ctx* fh_to_ctx (void*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfc_err_limited (char*) ; 
 int /*<<< orphan*/  v4l2_event_queue_fh (int /*<<< orphan*/ *,struct v4l2_event const*) ; 
 int vb2_dqbuf (TYPE_1__*,struct v4l2_buffer*,int) ; 

__attribute__((used)) static int vidioc_dqbuf(struct file *file, void *priv, struct v4l2_buffer *buf)
{
	const struct v4l2_event ev = {
		.type = V4L2_EVENT_EOS
	};
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	int ret;

	if (ctx->state == MFCINST_ERROR) {
		mfc_err_limited("Call on DQBUF after unrecoverable error\n");
		return -EIO;
	}
	if (buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		ret = vb2_dqbuf(&ctx->vq_src, buf, file->f_flags & O_NONBLOCK);
	} else if (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		ret = vb2_dqbuf(&ctx->vq_dst, buf, file->f_flags & O_NONBLOCK);
		if (ret == 0 && ctx->state == MFCINST_FINISHED
					&& list_empty(&ctx->vq_dst.done_list))
			v4l2_event_queue_fh(&ctx->fh, &ev);
	} else {
		ret = -EINVAL;
	}

	return ret;
}