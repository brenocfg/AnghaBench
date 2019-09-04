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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_bt_timings {scalar_t__ interlaced; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {struct v4l2_bt_timings bt; } ;
struct tda1997x_state {TYPE_1__ colorimetry; TYPE_2__ timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_FIELD_SEQ_TB ; 
 int /*<<< orphan*/  memset (struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tda1997x_fill_format(struct tda1997x_state *state,
				 struct v4l2_mbus_framefmt *format)
{
	const struct v4l2_bt_timings *bt;

	memset(format, 0, sizeof(*format));
	bt = &state->timings.bt;
	format->width = bt->width;
	format->height = bt->height;
	format->colorspace = state->colorimetry.colorspace;
	format->field = (bt->interlaced) ?
		V4L2_FIELD_SEQ_TB : V4L2_FIELD_NONE;
}