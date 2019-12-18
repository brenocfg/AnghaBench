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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {int pad; TYPE_1__ format; int /*<<< orphan*/  which; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct imx_media_pixfmt {int /*<<< orphan*/ * codes; } ;
struct imx7_csi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int EINVAL ; 
#define  IMX7_CSI_PAD_SINK 129 
#define  IMX7_CSI_PAD_SRC 128 
 struct v4l2_mbus_framefmt* imx7_csi_get_format (struct imx7_csi*,struct v4l2_subdev_pad_config*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_enum_mbus_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct imx_media_pixfmt* imx_media_find_mbus_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imx_media_try_colorimetry (TYPE_1__*,int) ; 

__attribute__((used)) static int imx7_csi_try_fmt(struct imx7_csi *csi,
			    struct v4l2_subdev_pad_config *cfg,
			    struct v4l2_subdev_format *sdformat,
			    const struct imx_media_pixfmt **cc)
{
	const struct imx_media_pixfmt *in_cc;
	struct v4l2_mbus_framefmt *in_fmt;
	u32 code;

	in_fmt = imx7_csi_get_format(csi, cfg, IMX7_CSI_PAD_SINK,
				     sdformat->which);
	if (!in_fmt)
		return -EINVAL;

	switch (sdformat->pad) {
	case IMX7_CSI_PAD_SRC:
		in_cc = imx_media_find_mbus_format(in_fmt->code, CS_SEL_ANY,
						   true);

		sdformat->format.width = in_fmt->width;
		sdformat->format.height = in_fmt->height;
		sdformat->format.code = in_fmt->code;
		*cc = in_cc;

		sdformat->format.colorspace = in_fmt->colorspace;
		sdformat->format.xfer_func = in_fmt->xfer_func;
		break;
	case IMX7_CSI_PAD_SINK:
		*cc = imx_media_find_mbus_format(sdformat->format.code,
						 CS_SEL_ANY, true);
		if (!*cc) {
			imx_media_enum_mbus_format(&code, 0, CS_SEL_ANY, false);
			*cc = imx_media_find_mbus_format(code, CS_SEL_ANY,
							 false);
			sdformat->format.code = (*cc)->codes[0];
		}
		break;
	default:
		return -EINVAL;
	}

	imx_media_try_colorimetry(&sdformat->format, false);

	return 0;
}