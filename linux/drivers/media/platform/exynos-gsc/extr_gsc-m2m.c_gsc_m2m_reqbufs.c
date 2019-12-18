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
typedef  scalar_t__ u32 ;
struct v4l2_requestbuffers {scalar_t__ type; scalar_t__ count; } ;
struct gsc_dev {TYPE_1__* variant; } ;
struct gsc_ctx {int /*<<< orphan*/  m2m_ctx; struct gsc_dev* gsc_dev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ in_buf_cnt; scalar_t__ out_buf_cnt; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 struct gsc_ctx* fh_to_ctx (void*) ; 
 int v4l2_m2m_reqbufs (struct file*,int /*<<< orphan*/ ,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int gsc_m2m_reqbufs(struct file *file, void *fh,
			  struct v4l2_requestbuffers *reqbufs)
{
	struct gsc_ctx *ctx = fh_to_ctx(fh);
	struct gsc_dev *gsc = ctx->gsc_dev;
	u32 max_cnt;

	max_cnt = (reqbufs->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) ?
		gsc->variant->in_buf_cnt : gsc->variant->out_buf_cnt;
	if (reqbufs->count > max_cnt)
		return -EINVAL;

	return v4l2_m2m_reqbufs(file, ctx->m2m_ctx, reqbufs);
}