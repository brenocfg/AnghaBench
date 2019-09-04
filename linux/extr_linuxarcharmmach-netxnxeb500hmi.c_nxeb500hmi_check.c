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
struct TYPE_2__ {int length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {TYPE_1__ green; } ;
struct clcd_fb {int dummy; } ;

/* Variables and functions */
 int clcdfb_check (struct clcd_fb*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static inline int nxeb500hmi_check(struct clcd_fb *fb, struct fb_var_screeninfo *var)
{
	var->green.length = 5;
	var->green.msb_right = 0;

	return clcdfb_check(fb, var);
}