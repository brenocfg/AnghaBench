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
struct v4l2_mbus_framefmt {int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int height; int flags; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ bt; } ;
struct adv7842_state {TYPE_2__ timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int V4L2_DV_FL_IS_CE_VIDEO ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  memset (struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adv7842_fill_format(struct adv7842_state *state,
				struct v4l2_mbus_framefmt *format)
{
	memset(format, 0, sizeof(*format));

	format->width = state->timings.bt.width;
	format->height = state->timings.bt.height;
	format->field = V4L2_FIELD_NONE;
	format->colorspace = V4L2_COLORSPACE_SRGB;

	if (state->timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO)
		format->colorspace = (state->timings.bt.height <= 576) ?
			V4L2_COLORSPACE_SMPTE170M : V4L2_COLORSPACE_REC709;
}