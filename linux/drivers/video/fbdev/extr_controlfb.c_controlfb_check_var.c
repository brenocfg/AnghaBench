#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fb_var_screeninfo {int dummy; } ;
struct fb_par_control {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  control_par_to_var (struct fb_par_control*,struct fb_var_screeninfo*) ; 
 int control_var_to_par (struct fb_var_screeninfo*,struct fb_par_control*,struct fb_info*) ; 

__attribute__((used)) static int controlfb_check_var (struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct fb_par_control par;
	int err;

	err = control_var_to_par(var, &par, info);
	if (err)
		return err;	
	control_par_to_var(&par, var);

	return 0;
}