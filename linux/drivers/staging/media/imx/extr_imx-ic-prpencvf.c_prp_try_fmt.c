#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ pad; TYPE_1__ format; int /*<<< orphan*/  which; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct prp_priv {int /*<<< orphan*/  rot_mode; } ;
struct imx_media_pixfmt {int /*<<< orphan*/ * codes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int /*<<< orphan*/  H_ALIGN_SINK ; 
 int /*<<< orphan*/  MAX_H_SINK ; 
 int /*<<< orphan*/  MAX_W_SINK ; 
 int /*<<< orphan*/  MIN_H_SINK ; 
 int /*<<< orphan*/  MIN_W_SINK ; 
 int /*<<< orphan*/  PRPENCVF_SINK_PAD ; 
 scalar_t__ PRPENCVF_SRC_PAD ; 
 int /*<<< orphan*/  S_ALIGN ; 
 int /*<<< orphan*/  V4L2_FIELD_ANY ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  W_ALIGN_SINK ; 
 struct v4l2_mbus_framefmt* __prp_get_fmt (struct prp_priv*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_enum_ipu_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx_media_pixfmt* imx_media_find_ipu_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_try_colorimetry (TYPE_1__*,int) ; 
 int /*<<< orphan*/  prp_bound_align_output (TYPE_1__*,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prp_try_fmt(struct prp_priv *priv,
			struct v4l2_subdev_pad_config *cfg,
			struct v4l2_subdev_format *sdformat,
			const struct imx_media_pixfmt **cc)
{
	struct v4l2_mbus_framefmt *infmt;

	*cc = imx_media_find_ipu_format(sdformat->format.code, CS_SEL_ANY);
	if (!*cc) {
		u32 code;

		imx_media_enum_ipu_format(&code, 0, CS_SEL_ANY);
		*cc = imx_media_find_ipu_format(code, CS_SEL_ANY);
		sdformat->format.code = (*cc)->codes[0];
	}

	infmt = __prp_get_fmt(priv, cfg, PRPENCVF_SINK_PAD, sdformat->which);

	if (sdformat->pad == PRPENCVF_SRC_PAD) {
		sdformat->format.field = infmt->field;

		prp_bound_align_output(&sdformat->format, infmt,
				       priv->rot_mode);

		/* propagate colorimetry from sink */
		sdformat->format.colorspace = infmt->colorspace;
		sdformat->format.xfer_func = infmt->xfer_func;
	} else {
		v4l_bound_align_image(&sdformat->format.width,
				      MIN_W_SINK, MAX_W_SINK, W_ALIGN_SINK,
				      &sdformat->format.height,
				      MIN_H_SINK, MAX_H_SINK, H_ALIGN_SINK,
				      S_ALIGN);

		if (sdformat->format.field == V4L2_FIELD_ANY)
			sdformat->format.field = V4L2_FIELD_NONE;
	}

	imx_media_try_colorimetry(&sdformat->format, true);
}