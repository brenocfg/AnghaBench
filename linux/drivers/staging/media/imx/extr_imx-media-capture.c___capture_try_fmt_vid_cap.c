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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_3__ format; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_5__ {int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct imx_media_pixfmt {scalar_t__ cs; } ;
struct capture_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int /*<<< orphan*/  CS_SEL_RGB ; 
 int /*<<< orphan*/  CS_SEL_YUV ; 
 int EINVAL ; 
 scalar_t__ IPUV3_COLORSPACE_YUV ; 
 int V4L2_FIELD_INTERLACED_BT ; 
 int V4L2_FIELD_INTERLACED_TB ; 
 scalar_t__ V4L2_FIELD_IS_INTERLACED (int /*<<< orphan*/ ) ; 
#define  V4L2_FIELD_SEQ_BT 129 
#define  V4L2_FIELD_SEQ_TB 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  imx_media_enum_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx_media_pixfmt* imx_media_find_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct imx_media_pixfmt* imx_media_find_ipu_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx_media_pixfmt* imx_media_find_mbus_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imx_media_mbus_fmt_to_pix_fmt (TYPE_2__*,TYPE_3__*,struct imx_media_pixfmt const*) ; 

__attribute__((used)) static int __capture_try_fmt_vid_cap(struct capture_priv *priv,
				     struct v4l2_subdev_format *fmt_src,
				     struct v4l2_format *f,
				     const struct imx_media_pixfmt **retcc,
				     struct v4l2_rect *compose)
{
	const struct imx_media_pixfmt *cc, *cc_src;

	cc_src = imx_media_find_ipu_format(fmt_src->format.code, CS_SEL_ANY);
	if (cc_src) {
		u32 fourcc, cs_sel;

		cs_sel = (cc_src->cs == IPUV3_COLORSPACE_YUV) ?
			CS_SEL_YUV : CS_SEL_RGB;
		fourcc = f->fmt.pix.pixelformat;

		cc = imx_media_find_format(fourcc, cs_sel, false);
		if (!cc) {
			imx_media_enum_format(&fourcc, 0, cs_sel);
			cc = imx_media_find_format(fourcc, cs_sel, false);
		}
	} else {
		cc_src = imx_media_find_mbus_format(fmt_src->format.code,
						    CS_SEL_ANY, true);
		if (WARN_ON(!cc_src))
			return -EINVAL;

		cc = cc_src;
	}

	/* allow IDMAC interweave but enforce field order from source */
	if (V4L2_FIELD_IS_INTERLACED(f->fmt.pix.field)) {
		switch (fmt_src->format.field) {
		case V4L2_FIELD_SEQ_TB:
			fmt_src->format.field = V4L2_FIELD_INTERLACED_TB;
			break;
		case V4L2_FIELD_SEQ_BT:
			fmt_src->format.field = V4L2_FIELD_INTERLACED_BT;
			break;
		default:
			break;
		}
	}

	imx_media_mbus_fmt_to_pix_fmt(&f->fmt.pix, &fmt_src->format, cc);

	if (retcc)
		*retcc = cc;

	if (compose) {
		compose->left = 0;
		compose->top = 0;
		compose->width = fmt_src->format.width;
		compose->height = fmt_src->format.height;
	}

	return 0;
}