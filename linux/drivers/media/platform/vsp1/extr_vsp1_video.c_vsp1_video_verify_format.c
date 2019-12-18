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
struct vsp1_video {TYPE_3__* rwpf; int /*<<< orphan*/  pad; } ;
struct TYPE_8__ {scalar_t__ code; scalar_t__ height; scalar_t__ width; } ;
struct v4l2_subdev_format {TYPE_4__ format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_6__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_7__ {TYPE_2__ format; TYPE_1__* fmtinfo; } ;
struct TYPE_5__ {scalar_t__ mbus; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 struct v4l2_subdev* vsp1_video_remote_subdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vsp1_video_verify_format(struct vsp1_video *video)
{
	struct v4l2_subdev_format fmt;
	struct v4l2_subdev *subdev;
	int ret;

	subdev = vsp1_video_remote_subdev(&video->pad, &fmt.pad);
	if (subdev == NULL)
		return -EINVAL;

	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(subdev, pad, get_fmt, NULL, &fmt);
	if (ret < 0)
		return ret == -ENOIOCTLCMD ? -EINVAL : ret;

	if (video->rwpf->fmtinfo->mbus != fmt.format.code ||
	    video->rwpf->format.height != fmt.format.height ||
	    video->rwpf->format.width != fmt.format.width)
		return -EINVAL;

	return 0;
}