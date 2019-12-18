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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_format; int /*<<< orphan*/  window_height; int /*<<< orphan*/  window_width; } ;
struct et8ek8_reglist {TYPE_1__ mode; } ;

/* Variables and functions */

__attribute__((used)) static void et8ek8_reglist_to_mbus(const struct et8ek8_reglist *reglist,
				   struct v4l2_mbus_framefmt *fmt)
{
	fmt->width = reglist->mode.window_width;
	fmt->height = reglist->mode.window_height;
	fmt->code = reglist->mode.bus_format;
}