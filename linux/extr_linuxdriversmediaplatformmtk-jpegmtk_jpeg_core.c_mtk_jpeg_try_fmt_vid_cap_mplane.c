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
struct TYPE_5__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_1__ pix_mp; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_2__ fmt; } ;
struct mtk_jpeg_fmt {int fourcc; } ;
struct TYPE_7__ {struct mtk_jpeg_fmt* fmt; } ;
struct mtk_jpeg_ctx {TYPE_4__* jpeg; TYPE_3__ cap_q; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_JPEG_FMT_TYPE_CAPTURE ; 
 int /*<<< orphan*/  debug ; 
 struct mtk_jpeg_ctx* mtk_jpeg_fh_to_ctx (void*) ; 
 struct mtk_jpeg_fmt* mtk_jpeg_find_format (struct mtk_jpeg_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtk_jpeg_try_fmt_mplane (struct v4l2_format*,struct mtk_jpeg_fmt*,struct mtk_jpeg_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int mtk_jpeg_try_fmt_vid_cap_mplane(struct file *file, void *priv,
					   struct v4l2_format *f)
{
	struct mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);
	struct mtk_jpeg_fmt *fmt;

	fmt = mtk_jpeg_find_format(ctx, f->fmt.pix_mp.pixelformat,
				   MTK_JPEG_FMT_TYPE_CAPTURE);
	if (!fmt)
		fmt = ctx->cap_q.fmt;

	v4l2_dbg(2, debug, &ctx->jpeg->v4l2_dev, "(%d) try_fmt:%c%c%c%c\n",
		 f->type,
		 (fmt->fourcc & 0xff),
		 (fmt->fourcc >>  8 & 0xff),
		 (fmt->fourcc >> 16 & 0xff),
		 (fmt->fourcc >> 24 & 0xff));

	return mtk_jpeg_try_fmt_mplane(f, fmt, ctx, MTK_JPEG_FMT_TYPE_CAPTURE);
}