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
typedef  scalar_t__ u32 ;
struct v4l2_mbus_framefmt {scalar_t__ code; scalar_t__ field; scalar_t__ height; scalar_t__ width; } ;
struct imx_media_pixfmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int /*<<< orphan*/  CS_SEL_YUV ; 
 int EINVAL ; 
 int /*<<< orphan*/  imx_media_enum_mbus_format (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct imx_media_pixfmt* imx_media_find_ipu_format (scalar_t__,int /*<<< orphan*/ ) ; 
 struct imx_media_pixfmt* imx_media_find_mbus_format (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_mbus_colorimetry (struct v4l2_mbus_framefmt*,struct imx_media_pixfmt const*) ; 

int imx_media_init_mbus_fmt(struct v4l2_mbus_framefmt *mbus,
			    u32 width, u32 height, u32 code, u32 field,
			    const struct imx_media_pixfmt **cc)
{
	const struct imx_media_pixfmt *lcc;

	mbus->width = width;
	mbus->height = height;
	mbus->field = field;
	if (code == 0)
		imx_media_enum_mbus_format(&code, 0, CS_SEL_YUV, false);
	lcc = imx_media_find_mbus_format(code, CS_SEL_ANY, false);
	if (!lcc) {
		lcc = imx_media_find_ipu_format(code, CS_SEL_ANY);
		if (!lcc)
			return -EINVAL;
	}

	mbus->code = code;
	init_mbus_colorimetry(mbus, lcc);
	if (cc)
		*cc = lcc;

	return 0;
}