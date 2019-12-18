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
struct work_struct {int dummy; } ;
struct vc_data {scalar_t__ vc_mode; TYPE_1__* vc_sw; } ;
struct TYPE_4__ {struct vc_data* d; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* con_scrolldelta ) (struct vc_data*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ KD_TEXT ; 
 scalar_t__ blank_timer_expired ; 
 int /*<<< orphan*/  change_console (struct vc_data*) ; 
 int /*<<< orphan*/  clear_selection () ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  do_blank_screen (int /*<<< orphan*/ ) ; 
 scalar_t__ do_poke_blanked_console ; 
 size_t fg_console ; 
 int /*<<< orphan*/  hide_cursor (struct vc_data*) ; 
 int /*<<< orphan*/  notify_update (struct vc_data*) ; 
 int /*<<< orphan*/  poke_blanked_console () ; 
 scalar_t__ scrollback_delta ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,scalar_t__) ; 
 TYPE_2__* vc_cons ; 
 scalar_t__ vc_cons_allocated (size_t) ; 
 size_t want_console ; 

__attribute__((used)) static void console_callback(struct work_struct *ignored)
{
	console_lock();

	if (want_console >= 0) {
		if (want_console != fg_console &&
		    vc_cons_allocated(want_console)) {
			hide_cursor(vc_cons[fg_console].d);
			change_console(vc_cons[want_console].d);
			/* we only changed when the console had already
			   been allocated - a new console is not created
			   in an interrupt routine */
		}
		want_console = -1;
	}
	if (do_poke_blanked_console) { /* do not unblank for a LED change */
		do_poke_blanked_console = 0;
		poke_blanked_console();
	}
	if (scrollback_delta) {
		struct vc_data *vc = vc_cons[fg_console].d;
		clear_selection();
		if (vc->vc_mode == KD_TEXT && vc->vc_sw->con_scrolldelta)
			vc->vc_sw->con_scrolldelta(vc, scrollback_delta);
		scrollback_delta = 0;
	}
	if (blank_timer_expired) {
		do_blank_screen(0);
		blank_timer_expired = 0;
	}
	notify_update(vc_cons[fg_console].d);

	console_unlock();
}