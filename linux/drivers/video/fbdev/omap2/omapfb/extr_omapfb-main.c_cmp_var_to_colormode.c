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
struct omapfb_colormode {scalar_t__ bits_per_pixel; int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_2__ {scalar_t__ length; } ;
struct fb_var_screeninfo {scalar_t__ bits_per_pixel; TYPE_1__ transp; TYPE_1__ blue; TYPE_1__ green; TYPE_1__ red; } ;

/* Variables and functions */
 scalar_t__ cmp_component (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cmp_var_to_colormode(struct fb_var_screeninfo *var,
		struct omapfb_colormode *color)
{
	if (var->bits_per_pixel == 0 ||
			var->red.length == 0 ||
			var->blue.length == 0 ||
			var->green.length == 0)
		return false;

	return var->bits_per_pixel == color->bits_per_pixel &&
		cmp_component(&var->red, &color->red) &&
		cmp_component(&var->green, &color->green) &&
		cmp_component(&var->blue, &color->blue) &&
		cmp_component(&var->transp, &color->transp);
}