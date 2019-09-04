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
struct TYPE_2__ {int width; int height; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_1__ format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev_fh {int /*<<< orphan*/ * pad; } ;
struct v4l2_subdev {int dummy; } ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 int /*<<< orphan*/  PREV_PAD_SINK ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  memset (struct v4l2_subdev_format*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preview_set_format (struct v4l2_subdev*,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int preview_init_formats(struct v4l2_subdev *sd,
				struct v4l2_subdev_fh *fh)
{
	struct v4l2_subdev_format format;

	memset(&format, 0, sizeof(format));
	format.pad = PREV_PAD_SINK;
	format.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	format.format.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	format.format.width = 4096;
	format.format.height = 4096;
	preview_set_format(sd, fh ? fh->pad : NULL, &format);

	return 0;
}