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
struct v4l2_pix_format_mplane {int height; scalar_t__ field; TYPE_1__* plane_fmt; } ;
struct fdp1_q_data {int vsize; int stride_y; int stride_c; struct v4l2_pix_format_mplane format; struct fdp1_fmt const* fmt; } ;
struct fdp1_fmt {int dummy; } ;
struct fdp1_ctx {struct fdp1_q_data cap_q; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_2__ {int bytesperline; } ;

/* Variables and functions */
 int V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_FIELD_INTERLACED_BT ; 
 scalar_t__ V4L2_FIELD_INTERLACED_TB ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  fdp1_try_fmt_capture (struct fdp1_ctx*,struct fdp1_fmt const**,struct v4l2_pix_format_mplane*) ; 
 int /*<<< orphan*/  fdp1_try_fmt_output (struct fdp1_ctx*,struct fdp1_fmt const**,struct v4l2_pix_format_mplane*) ; 
 struct fdp1_q_data* get_q_data (struct fdp1_ctx*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fdp1_set_format(struct fdp1_ctx *ctx,
			    struct v4l2_pix_format_mplane *pix,
			    enum v4l2_buf_type type)
{
	struct fdp1_q_data *q_data = get_q_data(ctx, type);
	const struct fdp1_fmt *fmtinfo;

	if (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fdp1_try_fmt_output(ctx, &fmtinfo, pix);
	else
		fdp1_try_fmt_capture(ctx, &fmtinfo, pix);

	q_data->fmt = fmtinfo;
	q_data->format = *pix;

	q_data->vsize = pix->height;
	if (pix->field != V4L2_FIELD_NONE)
		q_data->vsize /= 2;

	q_data->stride_y = pix->plane_fmt[0].bytesperline;
	q_data->stride_c = pix->plane_fmt[1].bytesperline;

	/* Adjust strides for interleaved buffers */
	if (pix->field == V4L2_FIELD_INTERLACED ||
	    pix->field == V4L2_FIELD_INTERLACED_TB ||
	    pix->field == V4L2_FIELD_INTERLACED_BT) {
		q_data->stride_y *= 2;
		q_data->stride_c *= 2;
	}

	/* Propagate the format from the output node to the capture node. */
	if (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		struct fdp1_q_data *dst_data = &ctx->cap_q;

		/*
		 * Copy the format, clear the per-plane bytes per line and image
		 * size, override the field and double the height if needed.
		 */
		dst_data->format = q_data->format;
		memset(dst_data->format.plane_fmt, 0,
		       sizeof(dst_data->format.plane_fmt));

		dst_data->format.field = V4L2_FIELD_NONE;
		if (pix->field == V4L2_FIELD_ALTERNATE)
			dst_data->format.height *= 2;

		fdp1_try_fmt_capture(ctx, &dst_data->fmt, &dst_data->format);

		dst_data->vsize = dst_data->format.height;
		dst_data->stride_y = dst_data->format.plane_fmt[0].bytesperline;
		dst_data->stride_c = dst_data->format.plane_fmt[1].bytesperline;
	}
}