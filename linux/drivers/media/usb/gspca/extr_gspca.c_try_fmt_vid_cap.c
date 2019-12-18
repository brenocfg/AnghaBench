#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct TYPE_5__ {TYPE_2__* cam_mode; } ;
struct gspca_dev {TYPE_4__* sd_desc; TYPE_1__ cam; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* try_fmt ) (struct gspca_dev*,struct v4l2_format*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  PDEBUG_MODE (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int gspca_get_mode (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct gspca_dev*,struct v4l2_format*) ; 
 int wxh_to_nearest_mode (struct gspca_dev*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_fmt_vid_cap(struct gspca_dev *gspca_dev,
			struct v4l2_format *fmt)
{
	int w, h, mode, mode2;

	w = fmt->fmt.pix.width;
	h = fmt->fmt.pix.height;

	PDEBUG_MODE(gspca_dev, D_CONF, "try fmt cap",
		    fmt->fmt.pix.pixelformat, w, h);

	/* search the nearest mode for width and height */
	mode = wxh_to_nearest_mode(gspca_dev, w, h, fmt->fmt.pix.pixelformat);

	/* OK if right palette */
	if (gspca_dev->cam.cam_mode[mode].pixelformat
						!= fmt->fmt.pix.pixelformat) {

		/* else, search the closest mode with the same pixel format */
		mode2 = gspca_get_mode(gspca_dev, mode,
					fmt->fmt.pix.pixelformat);
		if (mode2 >= 0)
			mode = mode2;
	}
	fmt->fmt.pix = gspca_dev->cam.cam_mode[mode];
	if (gspca_dev->sd_desc->try_fmt) {
		/* pass original resolution to subdriver try_fmt */
		fmt->fmt.pix.width = w;
		fmt->fmt.pix.height = h;
		gspca_dev->sd_desc->try_fmt(gspca_dev, fmt);
	}
	return mode;			/* used when s_fmt */
}