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
struct TYPE_5__ {int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_2__ format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_3__ pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; int /*<<< orphan*/  type; } ;
struct camss_video {int /*<<< orphan*/  bpl_alignment; int /*<<< orphan*/ * formats; int /*<<< orphan*/  type; int /*<<< orphan*/  nformats; } ;

/* Variables and functions */
 int EPIPE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 int video_find_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int video_mbus_to_pix_mp (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* video_remote_subdev (struct camss_video*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int video_get_subdev_format(struct camss_video *video,
				   struct v4l2_format *format)
{
	struct v4l2_subdev_format fmt;
	struct v4l2_subdev *subdev;
	u32 pad;
	int ret;

	subdev = video_remote_subdev(video, &pad);
	if (subdev == NULL)
		return -EPIPE;

	fmt.pad = pad;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;

	ret = v4l2_subdev_call(subdev, pad, get_fmt, NULL, &fmt);
	if (ret)
		return ret;

	ret = video_find_format(fmt.format.code,
				format->fmt.pix_mp.pixelformat,
				video->formats, video->nformats);
	if (ret < 0)
		return ret;

	format->type = video->type;

	return video_mbus_to_pix_mp(&fmt.format, &format->fmt.pix_mp,
				    &video->formats[ret], video->bpl_alignment);
}