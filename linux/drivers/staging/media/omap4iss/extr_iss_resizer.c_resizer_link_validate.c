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
struct TYPE_2__ {scalar_t__ width; scalar_t__ height; scalar_t__ code; } ;
struct v4l2_subdev_format {TYPE_1__ format; } ;
struct v4l2_subdev {int dummy; } ;
struct media_link {int dummy; } ;

/* Variables and functions */
 int EPIPE ; 

__attribute__((used)) static int resizer_link_validate(struct v4l2_subdev *sd,
				 struct media_link *link,
				 struct v4l2_subdev_format *source_fmt,
				 struct v4l2_subdev_format *sink_fmt)
{
	/* Check if the two ends match */
	if (source_fmt->format.width != sink_fmt->format.width ||
	    source_fmt->format.height != sink_fmt->format.height)
		return -EPIPE;

	if (source_fmt->format.code != sink_fmt->format.code)
		return -EPIPE;

	return 0;
}