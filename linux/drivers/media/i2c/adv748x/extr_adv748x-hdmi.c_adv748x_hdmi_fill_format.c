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
struct v4l2_mbus_framefmt {scalar_t__ field; int height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int height; int /*<<< orphan*/  width; scalar_t__ interlaced; } ;
struct TYPE_3__ {TYPE_2__ bt; } ;
struct adv748x_hdmi {TYPE_1__ timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_1X24 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  memset (struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adv748x_hdmi_fill_format(struct adv748x_hdmi *hdmi,
				     struct v4l2_mbus_framefmt *fmt)
{
	memset(fmt, 0, sizeof(*fmt));

	fmt->code = MEDIA_BUS_FMT_RGB888_1X24;
	fmt->field = hdmi->timings.bt.interlaced ?
			V4L2_FIELD_ALTERNATE : V4L2_FIELD_NONE;

	/* TODO: The colorspace depends on the AVI InfoFrame contents */
	fmt->colorspace = V4L2_COLORSPACE_SRGB;

	fmt->width = hdmi->timings.bt.width;
	fmt->height = hdmi->timings.bt.height;

	if (fmt->field == V4L2_FIELD_ALTERNATE)
		fmt->height /= 2;
}