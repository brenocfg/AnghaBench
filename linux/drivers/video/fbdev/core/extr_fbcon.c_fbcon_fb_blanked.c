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
struct vc_data {scalar_t__ vc_mode; } ;
struct fbcon_ops {size_t currcon; int blank_state; } ;
struct fb_info {struct fbcon_ops* fbcon_par; } ;
struct TYPE_2__ {struct vc_data* d; } ;

/* Variables and functions */
 scalar_t__ KD_TEXT ; 
 size_t* con2fb_map ; 
 scalar_t__ con_is_visible (struct vc_data*) ; 
 int /*<<< orphan*/  do_blank_screen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_unblank_screen (int /*<<< orphan*/ ) ; 
 struct fb_info** registered_fb ; 
 TYPE_1__* vc_cons ; 

void fbcon_fb_blanked(struct fb_info *info, int blank)
{
	struct fbcon_ops *ops = info->fbcon_par;
	struct vc_data *vc;

	if (!ops || ops->currcon < 0)
		return;

	vc = vc_cons[ops->currcon].d;
	if (vc->vc_mode != KD_TEXT ||
			registered_fb[con2fb_map[ops->currcon]] != info)
		return;

	if (con_is_visible(vc)) {
		if (blank)
			do_blank_screen(0);
		else
			do_unblank_screen(0);
	}
	ops->blank_state = blank;
}