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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct v4l2_async_notifier {int dummy; } ;
struct cal_fmt {int /*<<< orphan*/  fourcc; } ;
struct TYPE_5__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_2__ pix; } ;
struct TYPE_6__ {TYPE_1__ fmt; int /*<<< orphan*/  type; } ;
struct cal_ctx {struct v4l2_mbus_framefmt m_fmt; struct cal_fmt const* fmt; TYPE_3__ v_fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int __subdev_get_format (struct cal_ctx*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  cal_calc_format_size (struct cal_ctx*,struct cal_fmt const*,TYPE_3__*) ; 
 int /*<<< orphan*/  ctx_dbg (int,struct cal_ctx*,char*,int /*<<< orphan*/ ) ; 
 struct cal_fmt* find_format_by_code (struct cal_ctx*,int /*<<< orphan*/ ) ; 
 struct cal_ctx* notifier_to_ctx (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (TYPE_2__*,struct v4l2_mbus_framefmt*) ; 

__attribute__((used)) static int cal_async_complete(struct v4l2_async_notifier *notifier)
{
	struct cal_ctx *ctx = notifier_to_ctx(notifier);
	const struct cal_fmt *fmt;
	struct v4l2_mbus_framefmt mbus_fmt;
	int ret;

	ret = __subdev_get_format(ctx, &mbus_fmt);
	if (ret)
		return ret;

	fmt = find_format_by_code(ctx, mbus_fmt.code);
	if (!fmt) {
		ctx_dbg(3, ctx, "mbus code format (0x%08x) not found.\n",
			mbus_fmt.code);
		return -EINVAL;
	}

	/* Save current subdev format */
	v4l2_fill_pix_format(&ctx->v_fmt.fmt.pix, &mbus_fmt);
	ctx->v_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ctx->v_fmt.fmt.pix.pixelformat  = fmt->fourcc;
	cal_calc_format_size(ctx, fmt, &ctx->v_fmt);
	ctx->fmt = fmt;
	ctx->m_fmt = mbus_fmt;

	return 0;
}