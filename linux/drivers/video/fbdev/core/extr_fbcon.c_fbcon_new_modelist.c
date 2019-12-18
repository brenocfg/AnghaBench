#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int /*<<< orphan*/  vc_num; } ;
struct fb_videomode {int dummy; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int /*<<< orphan*/  modelist; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {struct vc_data* d; } ;

/* Variables and functions */
 size_t* con2fb_map ; 
 int /*<<< orphan*/  display_to_var (struct fb_var_screeninfo*,TYPE_2__*) ; 
 TYPE_2__* fb_display ; 
 struct fb_videomode* fb_find_nearest_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_videomode_to_var (struct fb_var_screeninfo*,struct fb_videomode const*) ; 
 int /*<<< orphan*/  fbcon_set_disp (struct fb_info*,struct fb_var_screeninfo*,int /*<<< orphan*/ ) ; 
 int first_fb_vc ; 
 int last_fb_vc ; 
 struct fb_info** registered_fb ; 
 TYPE_1__* vc_cons ; 

void fbcon_new_modelist(struct fb_info *info)
{
	int i;
	struct vc_data *vc;
	struct fb_var_screeninfo var;
	const struct fb_videomode *mode;

	for (i = first_fb_vc; i <= last_fb_vc; i++) {
		if (registered_fb[con2fb_map[i]] != info)
			continue;
		if (!fb_display[i].mode)
			continue;
		vc = vc_cons[i].d;
		display_to_var(&var, &fb_display[i]);
		mode = fb_find_nearest_mode(fb_display[i].mode,
					    &info->modelist);
		fb_videomode_to_var(&var, mode);
		fbcon_set_disp(info, &var, vc->vc_num);
	}
}