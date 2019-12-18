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
struct TYPE_6__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct cedrus_ctx {TYPE_3__ src_fmt; TYPE_1__ dst_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_1K ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG2_SLICE ; 
 struct cedrus_ctx* cedrus_file2ctx (struct file*) ; 
 int /*<<< orphan*/  cedrus_prepare_format (TYPE_3__*) ; 

__attribute__((used)) static int cedrus_g_fmt_vid_out(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct cedrus_ctx *ctx = cedrus_file2ctx(file);

	/* Fall back to dummy default by lack of hardware configuration. */
	if (!ctx->dst_fmt.width || !ctx->dst_fmt.height) {
		f->fmt.pix.pixelformat = V4L2_PIX_FMT_MPEG2_SLICE;
		f->fmt.pix.sizeimage = SZ_1K;
		cedrus_prepare_format(&f->fmt.pix);

		return 0;
	}

	f->fmt.pix = ctx->src_fmt;

	return 0;
}