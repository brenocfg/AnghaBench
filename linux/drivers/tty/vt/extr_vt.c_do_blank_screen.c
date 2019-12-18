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
struct vc_data {scalar_t__ vc_mode; int /*<<< orphan*/  vc_num; TYPE_1__* vc_sw; } ;
struct TYPE_4__ {struct vc_data* d; } ;
struct TYPE_3__ {int (* con_blank ) (struct vc_data*,int,int) ;} ;

/* Variables and functions */
 scalar_t__ KD_TEXT ; 
 int /*<<< orphan*/  VT_EVENT_BLANK ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 scalar_t__ blank_off ; 
 scalar_t__ blank_state ; 
 scalar_t__ blank_timer_expired ; 
 scalar_t__ blank_vesa_wait ; 
 scalar_t__ console_blank_hook (int) ; 
 int console_blanked ; 
 int /*<<< orphan*/  console_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 size_t fg_console ; 
 int /*<<< orphan*/  hide_cursor (struct vc_data*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  save_screen (struct vc_data*) ; 
 int /*<<< orphan*/  set_origin (struct vc_data*) ; 
 int stub1 (struct vc_data*,int,int) ; 
 int stub2 (struct vc_data*,int,int) ; 
 int stub3 (struct vc_data*,int,int) ; 
 TYPE_2__* vc_cons ; 
 int vesa_blank_mode ; 
 scalar_t__ vesa_off_interval ; 
 int /*<<< orphan*/  vt_event_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void do_blank_screen(int entering_gfx)
{
	struct vc_data *vc = vc_cons[fg_console].d;
	int i;

	might_sleep();

	WARN_CONSOLE_UNLOCKED();

	if (console_blanked) {
		if (blank_state == blank_vesa_wait) {
			blank_state = blank_off;
			vc->vc_sw->con_blank(vc, vesa_blank_mode + 1, 0);
		}
		return;
	}

	/* entering graphics mode? */
	if (entering_gfx) {
		hide_cursor(vc);
		save_screen(vc);
		vc->vc_sw->con_blank(vc, -1, 1);
		console_blanked = fg_console + 1;
		blank_state = blank_off;
		set_origin(vc);
		return;
	}

	blank_state = blank_off;

	/* don't blank graphics */
	if (vc->vc_mode != KD_TEXT) {
		console_blanked = fg_console + 1;
		return;
	}

	hide_cursor(vc);
	del_timer_sync(&console_timer);
	blank_timer_expired = 0;

	save_screen(vc);
	/* In case we need to reset origin, blanking hook returns 1 */
	i = vc->vc_sw->con_blank(vc, vesa_off_interval ? 1 : (vesa_blank_mode + 1), 0);
	console_blanked = fg_console + 1;
	if (i)
		set_origin(vc);

	if (console_blank_hook && console_blank_hook(1))
		return;

	if (vesa_off_interval && vesa_blank_mode) {
		blank_state = blank_vesa_wait;
		mod_timer(&console_timer, jiffies + vesa_off_interval);
	}
	vt_event_post(VT_EVENT_BLANK, vc->vc_num, vc->vc_num);
}