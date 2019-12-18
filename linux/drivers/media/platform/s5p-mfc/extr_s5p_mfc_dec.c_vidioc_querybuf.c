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
struct TYPE_6__ {TYPE_2__* planes; } ;
struct v4l2_buffer {scalar_t__ memory; int length; TYPE_3__ m; int /*<<< orphan*/  type; } ;
struct s5p_mfc_ctx {scalar_t__ state; int /*<<< orphan*/  vq_dst; int /*<<< orphan*/  vq_src; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mem_offset; } ;
struct TYPE_5__ {TYPE_1__ m; } ;

/* Variables and functions */
 scalar_t__ DST_QUEUE_OFF_BASE ; 
 int EINVAL ; 
 scalar_t__ MFCINST_GOT_INST ; 
 scalar_t__ MFCINST_RUNNING ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 struct s5p_mfc_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int vb2_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int vidioc_querybuf(struct file *file, void *priv,
						   struct v4l2_buffer *buf)
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	int ret;
	int i;

	if (buf->memory != V4L2_MEMORY_MMAP) {
		mfc_err("Only mmapped buffers can be used\n");
		return -EINVAL;
	}
	mfc_debug(2, "State: %d, buf->type: %d\n", ctx->state, buf->type);
	if (ctx->state == MFCINST_GOT_INST &&
			buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		ret = vb2_querybuf(&ctx->vq_src, buf);
	} else if (ctx->state == MFCINST_RUNNING &&
			buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		ret = vb2_querybuf(&ctx->vq_dst, buf);
		for (i = 0; i < buf->length; i++)
			buf->m.planes[i].m.mem_offset += DST_QUEUE_OFF_BASE;
	} else {
		mfc_err("vidioc_querybuf called in an inappropriate state\n");
		ret = -EINVAL;
	}
	mfc_debug_leave();
	return ret;
}