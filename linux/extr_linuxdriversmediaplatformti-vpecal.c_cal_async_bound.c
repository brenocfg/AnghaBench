#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_subdev_mbus_code_enum {int index; scalar_t__ code; } ;
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int dummy; } ;
struct cal_fmt {scalar_t__ code; int /*<<< orphan*/  fourcc; } ;
struct cal_ctx {int num_active_fmt; struct cal_fmt** active_fmt; struct v4l2_subdev* sensor; } ;
typedef  int /*<<< orphan*/  mbus_code ;

/* Variables and functions */
 int ARRAY_SIZE (struct cal_fmt*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cal_complete_ctx (struct cal_ctx*) ; 
 struct cal_fmt* cal_formats ; 
 int /*<<< orphan*/  ctx_dbg (int,struct cal_ctx*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ctx_err (struct cal_ctx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_info (struct cal_ctx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_mbus_code ; 
 int /*<<< orphan*/  fourcc_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_subdev_mbus_code_enum*,int /*<<< orphan*/ ,int) ; 
 struct cal_ctx* notifier_to_ctx (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_mbus_code_enum*) ; 

__attribute__((used)) static int cal_async_bound(struct v4l2_async_notifier *notifier,
			   struct v4l2_subdev *subdev,
			   struct v4l2_async_subdev *asd)
{
	struct cal_ctx *ctx = notifier_to_ctx(notifier);
	struct v4l2_subdev_mbus_code_enum mbus_code;
	int ret = 0;
	int i, j, k;

	if (ctx->sensor) {
		ctx_info(ctx, "Rejecting subdev %s (Already set!!)",
			 subdev->name);
		return 0;
	}

	ctx->sensor = subdev;
	ctx_dbg(1, ctx, "Using sensor %s for capture\n", subdev->name);

	/* Enumerate sub device formats and enable all matching local formats */
	ctx->num_active_fmt = 0;
	for (j = 0, i = 0; ret != -EINVAL; ++j) {
		struct cal_fmt *fmt;

		memset(&mbus_code, 0, sizeof(mbus_code));
		mbus_code.index = j;
		ret = v4l2_subdev_call(subdev, pad, enum_mbus_code,
				       NULL, &mbus_code);
		if (ret)
			continue;

		ctx_dbg(2, ctx,
			"subdev %s: code: %04x idx: %d\n",
			subdev->name, mbus_code.code, j);

		for (k = 0; k < ARRAY_SIZE(cal_formats); k++) {
			fmt = &cal_formats[k];

			if (mbus_code.code == fmt->code) {
				ctx->active_fmt[i] = fmt;
				ctx_dbg(2, ctx,
					"matched fourcc: %s: code: %04x idx: %d\n",
					fourcc_to_str(fmt->fourcc),
					fmt->code, i);
				ctx->num_active_fmt = ++i;
			}
		}
	}

	if (i == 0) {
		ctx_err(ctx, "No suitable format reported by subdev %s\n",
			subdev->name);
		return -EINVAL;
	}

	cal_complete_ctx(ctx);

	return 0;
}