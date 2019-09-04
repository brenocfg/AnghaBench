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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ov7670_info {TYPE_1__* fmt; TYPE_2__* devtype; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {TYPE_3__* win_sizes; } ;
struct TYPE_4__ {int /*<<< orphan*/  mbus_code; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void ov7670_get_default_format(struct v4l2_subdev *sd,
				      struct v4l2_mbus_framefmt *format)
{
	struct ov7670_info *info = to_state(sd);

	format->width = info->devtype->win_sizes[0].width;
	format->height = info->devtype->win_sizes[0].height;
	format->colorspace = info->fmt->colorspace;
	format->code = info->fmt->mbus_code;
	format->field = V4L2_FIELD_NONE;
}