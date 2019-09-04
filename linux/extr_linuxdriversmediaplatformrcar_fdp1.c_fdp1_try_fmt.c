#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_2__ pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct fdp1_ctx {int /*<<< orphan*/  fdp1; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (scalar_t__) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdp1_try_fmt_capture (struct fdp1_ctx*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fdp1_try_fmt_output (struct fdp1_ctx*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 struct fdp1_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int fdp1_try_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
	struct fdp1_ctx *ctx = fh_to_ctx(priv);

	if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fdp1_try_fmt_output(ctx, NULL, &f->fmt.pix_mp);
	else
		fdp1_try_fmt_capture(ctx, NULL, &f->fmt.pix_mp);

	dprintk(ctx->fdp1, "Try %s format: %4.4s (0x%08x) %ux%u field %u\n",
		V4L2_TYPE_IS_OUTPUT(f->type) ? "output" : "capture",
		(char *)&f->fmt.pix_mp.pixelformat, f->fmt.pix_mp.pixelformat,
		f->fmt.pix_mp.width, f->fmt.pix_mp.height, f->fmt.pix_mp.field);

	return 0;
}