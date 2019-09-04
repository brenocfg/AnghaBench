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
struct v4l2_fract {int dummy; } ;
struct TYPE_4__ {struct v4l2_fract timeperframe; } ;
struct TYPE_5__ {TYPE_1__ output; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_2__ parm; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  framerate; } ;
struct coda_ctx {TYPE_3__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  coda_approximate_timeperframe (struct v4l2_fract*) ; 
 int /*<<< orphan*/  coda_timeperframe_to_frate (struct v4l2_fract*) ; 
 struct coda_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int coda_s_parm(struct file *file, void *fh, struct v4l2_streamparm *a)
{
	struct coda_ctx *ctx = fh_to_ctx(fh);
	struct v4l2_fract *tpf;

	if (a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	tpf = &a->parm.output.timeperframe;
	coda_approximate_timeperframe(tpf);
	ctx->params.framerate = coda_timeperframe_to_frate(tpf);

	return 0;
}