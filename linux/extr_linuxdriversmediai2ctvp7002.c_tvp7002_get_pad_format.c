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
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_4__ format; } ;
struct v4l2_subdev {int dummy; } ;
struct tvp7002 {TYPE_3__* current_timings; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {TYPE_1__ bt; } ;
struct TYPE_7__ {int /*<<< orphan*/  color_space; int /*<<< orphan*/  scanmode; TYPE_2__ timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_YUYV10_1X20 ; 
 struct tvp7002* to_tvp7002 (struct v4l2_subdev*) ; 

__attribute__((used)) static int
tvp7002_get_pad_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
		       struct v4l2_subdev_format *fmt)
{
	struct tvp7002 *tvp7002 = to_tvp7002(sd);

	fmt->format.code = MEDIA_BUS_FMT_YUYV10_1X20;
	fmt->format.width = tvp7002->current_timings->timings.bt.width;
	fmt->format.height = tvp7002->current_timings->timings.bt.height;
	fmt->format.field = tvp7002->current_timings->scanmode;
	fmt->format.colorspace = tvp7002->current_timings->color_space;

	return 0;
}