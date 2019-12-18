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
struct v4l2_buffer {scalar_t__ type; int /*<<< orphan*/  flags; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct coda_ctx {scalar_t__ inst_type; TYPE_1__ fh; } ;

/* Variables and functions */
 scalar_t__ CODA_INST_DECODER ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_LAST ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 struct coda_ctx* fh_to_ctx (void*) ; 
 int v4l2_m2m_dqbuf (struct file*,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 

__attribute__((used)) static int coda_dqbuf(struct file *file, void *priv, struct v4l2_buffer *buf)
{
	struct coda_ctx *ctx = fh_to_ctx(priv);
	int ret;

	ret = v4l2_m2m_dqbuf(file, ctx->fh.m2m_ctx, buf);

	if (ctx->inst_type == CODA_INST_DECODER &&
	    buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		buf->flags &= ~V4L2_BUF_FLAG_LAST;

	return ret;
}