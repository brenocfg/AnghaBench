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
struct TYPE_2__ {int step_width; int step_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_frmsizeenum {scalar_t__ pixel_format; TYPE_1__ stepwise; int /*<<< orphan*/  type; scalar_t__ index; } ;
struct file {int dummy; } ;
struct coda_q_data {scalar_t__ fourcc; } ;
struct coda_ctx {scalar_t__ inst_type; int /*<<< orphan*/  dev; } ;
struct coda_codec {int /*<<< orphan*/  max_h; int /*<<< orphan*/  max_w; } ;

/* Variables and functions */
 scalar_t__ CODA_INST_ENCODER ; 
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  MIN_H ; 
 int /*<<< orphan*/  MIN_W ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_CONTINUOUS ; 
 scalar_t__ V4L2_PIX_FMT_YUV420 ; 
 struct coda_codec* coda_find_codec (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ coda_format_normalize_yuv (scalar_t__) ; 
 struct coda_ctx* fh_to_ctx (void*) ; 
 struct coda_q_data* get_q_data (struct coda_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_enum_framesizes(struct file *file, void *fh,
				struct v4l2_frmsizeenum *fsize)
{
	struct coda_ctx *ctx = fh_to_ctx(fh);
	struct coda_q_data *q_data_dst;
	const struct coda_codec *codec;

	if (ctx->inst_type != CODA_INST_ENCODER)
		return -ENOTTY;

	if (fsize->index)
		return -EINVAL;

	if (coda_format_normalize_yuv(fsize->pixel_format) ==
	    V4L2_PIX_FMT_YUV420) {
		q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
		codec = coda_find_codec(ctx->dev, fsize->pixel_format,
					q_data_dst->fourcc);
	} else {
		codec = coda_find_codec(ctx->dev, V4L2_PIX_FMT_YUV420,
					fsize->pixel_format);
	}
	if (!codec)
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = MIN_W;
	fsize->stepwise.max_width = codec->max_w;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.min_height = MIN_H;
	fsize->stepwise.max_height = codec->max_h;
	fsize->stepwise.step_height = 1;

	return 0;
}