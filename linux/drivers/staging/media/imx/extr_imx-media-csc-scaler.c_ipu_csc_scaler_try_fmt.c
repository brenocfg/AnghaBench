#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int field; int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; int /*<<< orphan*/  type; } ;
struct ipu_image {TYPE_1__ pix; } ;
struct ipu_csc_scaler_q_data {TYPE_1__ cur_fmt; } ;
struct ipu_csc_scaler_ctx {int /*<<< orphan*/  rot_mode; } ;
struct file {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_DEFAULT ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int V4L2_FIELD_ANY ; 
 int V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 struct ipu_csc_scaler_ctx* fh_to_ctx (void*) ; 
 struct ipu_csc_scaler_q_data* get_q_data (struct ipu_csc_scaler_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_image_convert_adjust (struct ipu_image*,struct ipu_image*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipu_csc_scaler_try_fmt(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct ipu_csc_scaler_ctx *ctx = fh_to_ctx(priv);
	struct ipu_csc_scaler_q_data *q_data = get_q_data(ctx, f->type);
	struct ipu_image test_in, test_out;
	enum v4l2_field field;

	field = f->fmt.pix.field;
	if (field == V4L2_FIELD_ANY)
		field = V4L2_FIELD_NONE;
	else if (field != V4L2_FIELD_NONE)
		return -EINVAL;

	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		struct ipu_csc_scaler_q_data *q_data_in =
			get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);

		test_out.pix = f->fmt.pix;
		test_in.pix = q_data_in->cur_fmt;
	} else {
		struct ipu_csc_scaler_q_data *q_data_out =
			get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

		test_in.pix = f->fmt.pix;
		test_out.pix = q_data_out->cur_fmt;
	}

	ipu_image_convert_adjust(&test_in, &test_out, ctx->rot_mode);

	f->fmt.pix = (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) ?
		test_out.pix : test_in.pix;

	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		f->fmt.pix.colorspace = q_data->cur_fmt.colorspace;
		f->fmt.pix.ycbcr_enc = q_data->cur_fmt.ycbcr_enc;
		f->fmt.pix.xfer_func = q_data->cur_fmt.xfer_func;
		f->fmt.pix.quantization = q_data->cur_fmt.quantization;
	} else if (f->fmt.pix.colorspace == V4L2_COLORSPACE_DEFAULT) {
		f->fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;
		f->fmt.pix.ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
		f->fmt.pix.xfer_func = V4L2_XFER_FUNC_DEFAULT;
		f->fmt.pix.quantization = V4L2_QUANTIZATION_DEFAULT;
	}

	return 0;
}