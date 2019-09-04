#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_mbus_framefmt {scalar_t__ field; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct TYPE_5__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct unicam_fmt {int /*<<< orphan*/  code; int /*<<< orphan*/  fourcc; } ;
struct unicam_device {int /*<<< orphan*/  sensor_config; int /*<<< orphan*/  sensor; struct unicam_fmt* active_fmts; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct unicam_fmt* find_format_by_pix (struct unicam_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int unicam_calc_format_size_bpl (struct unicam_device*,struct unicam_fmt const*,struct v4l2_format*) ; 
 int /*<<< orphan*/  unicam_dbg (int,struct unicam_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unicam_info (struct unicam_device*,char*) ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (struct v4l2_mbus_framefmt*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (TYPE_2__*,struct v4l2_mbus_framefmt*) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_format*) ; 
 struct unicam_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int unicam_try_fmt_vid_cap(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct unicam_device *dev = video_drvdata(file);
	const struct unicam_fmt *fmt;
	struct v4l2_subdev_format sd_fmt = {
		.which = V4L2_SUBDEV_FORMAT_TRY,
	};
	struct v4l2_mbus_framefmt *mbus_fmt = &sd_fmt.format;
	int ret;

	fmt = find_format_by_pix(dev, f->fmt.pix.pixelformat);
	if (!fmt) {
		unicam_dbg(3, dev, "Fourcc format (0x%08x) not found. Use default of %08X\n",
			   f->fmt.pix.pixelformat, dev->active_fmts[0].fourcc);

		/* Just get the first one enumerated */
		fmt = &dev->active_fmts[0];
		f->fmt.pix.pixelformat = fmt->fourcc;
	}

	v4l2_fill_mbus_format(mbus_fmt, &f->fmt.pix, fmt->code);
	/*
	 * No support for receiving interlaced video, so never
	 * request it from the sensor subdev.
	 */
	mbus_fmt->field = V4L2_FIELD_NONE;

	ret = v4l2_subdev_call(dev->sensor, pad, set_fmt, dev->sensor_config,
			       &sd_fmt);
	if (ret && ret != -ENOIOCTLCMD && ret != -ENODEV)
		return ret;

	if (mbus_fmt->field != V4L2_FIELD_NONE)
		unicam_info(dev, "Sensor trying to send interlaced video - results may be unpredictable\n");

	v4l2_fill_pix_format(&f->fmt.pix, &sd_fmt.format);

	return unicam_calc_format_size_bpl(dev, fmt, f);
}