#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fb_var_screeninfo {scalar_t__ xres; scalar_t__ yres; } ;
struct TYPE_3__ {scalar_t__ hdp; scalar_t__ vdp; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* car_modes ; 

__attribute__((used)) static int carmine_find_mode(const struct fb_var_screeninfo *var)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(car_modes); i++)
		if (car_modes[i].hdp == var->xres &&
		    car_modes[i].vdp == var->yres)
			return i;
	return -EINVAL;
}