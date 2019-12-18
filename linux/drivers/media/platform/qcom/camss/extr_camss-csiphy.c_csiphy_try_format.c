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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; void* height; void* width; int /*<<< orphan*/  code; } ;
struct csiphy_device {unsigned int nformats; TYPE_1__* formats; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  MSM_CSID_PAD_SINK ; 
#define  MSM_CSIPHY_PAD_SINK 129 
#define  MSM_CSIPHY_PAD_SRC 128 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct v4l2_mbus_framefmt* __csiphy_get_format (struct csiphy_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int) ; 
 void* clamp_t (int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void csiphy_try_format(struct csiphy_device *csiphy,
			      struct v4l2_subdev_pad_config *cfg,
			      unsigned int pad,
			      struct v4l2_mbus_framefmt *fmt,
			      enum v4l2_subdev_format_whence which)
{
	unsigned int i;

	switch (pad) {
	case MSM_CSIPHY_PAD_SINK:
		/* Set format on sink pad */

		for (i = 0; i < csiphy->nformats; i++)
			if (fmt->code == csiphy->formats[i].code)
				break;

		/* If not found, use UYVY as default */
		if (i >= csiphy->nformats)
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

		fmt->width = clamp_t(u32, fmt->width, 1, 8191);
		fmt->height = clamp_t(u32, fmt->height, 1, 8191);

		fmt->field = V4L2_FIELD_NONE;
		fmt->colorspace = V4L2_COLORSPACE_SRGB;

		break;

	case MSM_CSIPHY_PAD_SRC:
		/* Set and return a format same as sink pad */

		*fmt = *__csiphy_get_format(csiphy, cfg, MSM_CSID_PAD_SINK,
					    which);

		break;
	}
}