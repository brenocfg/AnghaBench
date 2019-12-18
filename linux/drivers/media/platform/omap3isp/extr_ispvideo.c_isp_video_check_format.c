#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pixelformat; scalar_t__ height; scalar_t__ width; scalar_t__ bytesperline; scalar_t__ sizeimage; scalar_t__ field; } ;
struct TYPE_9__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_4__ fmt; } ;
struct TYPE_6__ {scalar_t__ pixelformat; scalar_t__ height; scalar_t__ width; scalar_t__ bytesperline; scalar_t__ sizeimage; scalar_t__ field; } ;
struct TYPE_7__ {TYPE_1__ pix; } ;
struct TYPE_10__ {TYPE_2__ fmt; } ;
struct isp_video_fh {TYPE_5__ format; } ;
struct isp_video {int dummy; } ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int EINVAL ; 
 int __isp_video_get_format (struct isp_video*,struct v4l2_format*) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_format*,TYPE_5__*,int) ; 

__attribute__((used)) static int
isp_video_check_format(struct isp_video *video, struct isp_video_fh *vfh)
{
	struct v4l2_format format;
	int ret;

	memcpy(&format, &vfh->format, sizeof(format));
	ret = __isp_video_get_format(video, &format);
	if (ret < 0)
		return ret;

	if (vfh->format.fmt.pix.pixelformat != format.fmt.pix.pixelformat ||
	    vfh->format.fmt.pix.height != format.fmt.pix.height ||
	    vfh->format.fmt.pix.width != format.fmt.pix.width ||
	    vfh->format.fmt.pix.bytesperline != format.fmt.pix.bytesperline ||
	    vfh->format.fmt.pix.sizeimage != format.fmt.pix.sizeimage ||
	    vfh->format.fmt.pix.field != format.fmt.pix.field)
		return -EINVAL;

	return 0;
}