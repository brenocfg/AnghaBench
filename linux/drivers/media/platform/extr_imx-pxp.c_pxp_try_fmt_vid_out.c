#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct pxp_fmt {int types; } ;
struct pxp_ctx {TYPE_1__* dev; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  fourcc; } ;
struct TYPE_5__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int MEM2MEM_OUTPUT ; 
 scalar_t__ V4L2_COLORSPACE_REC709 ; 
 struct pxp_ctx* file2ctx (struct file*) ; 
 struct pxp_fmt* find_format (struct v4l2_format*) ; 
 TYPE_4__* formats ; 
 int pxp_try_fmt (struct v4l2_format*,struct pxp_fmt*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxp_try_fmt_vid_out(struct file *file, void *priv,
			       struct v4l2_format *f)
{
	struct pxp_fmt *fmt;
	struct pxp_ctx *ctx = file2ctx(file);

	fmt = find_format(f);
	if (!fmt) {
		f->fmt.pix.pixelformat = formats[0].fourcc;
		fmt = find_format(f);
	}
	if (!(fmt->types & MEM2MEM_OUTPUT)) {
		v4l2_err(&ctx->dev->v4l2_dev,
			 "Fourcc format (0x%08x) invalid.\n",
			 f->fmt.pix.pixelformat);
		return -EINVAL;
	}

	if (!f->fmt.pix.colorspace)
		f->fmt.pix.colorspace = V4L2_COLORSPACE_REC709;

	return pxp_try_fmt(f, fmt);
}