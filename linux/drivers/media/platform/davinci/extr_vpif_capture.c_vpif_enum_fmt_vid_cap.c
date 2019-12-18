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
struct video_device {int dummy; } ;
struct v4l2_fmtdesc {scalar_t__ index; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ if_type; } ;
struct TYPE_4__ {TYPE_1__ iface; } ;
struct channel_obj {TYPE_2__ vpifparams; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV16 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR8 ; 
 scalar_t__ VPIF_IF_RAW_BAYER ; 
 int /*<<< orphan*/  debug ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpif_enum_fmt_vid_cap(struct file *file, void  *priv,
					struct v4l2_fmtdesc *fmt)
{
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);

	if (fmt->index != 0) {
		vpif_dbg(1, debug, "Invalid format index\n");
		return -EINVAL;
	}

	/* Fill in the information about format */
	if (ch->vpifparams.iface.if_type == VPIF_IF_RAW_BAYER)
		fmt->pixelformat = V4L2_PIX_FMT_SBGGR8;
	else
		fmt->pixelformat = V4L2_PIX_FMT_NV16;
	return 0;
}