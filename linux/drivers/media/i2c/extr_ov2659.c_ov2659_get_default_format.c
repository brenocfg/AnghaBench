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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 TYPE_2__* ov2659_formats ; 
 TYPE_1__* ov2659_framesizes ; 

__attribute__((used)) static void ov2659_get_default_format(struct v4l2_mbus_framefmt *format)
{
	format->width = ov2659_framesizes[2].width;
	format->height = ov2659_framesizes[2].height;
	format->colorspace = V4L2_COLORSPACE_SRGB;
	format->code = ov2659_formats[0].code;
	format->field = V4L2_FIELD_NONE;
}