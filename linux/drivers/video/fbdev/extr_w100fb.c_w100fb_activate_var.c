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
struct w100fb_par {int /*<<< orphan*/  blanked; TYPE_1__* mach; } ;
struct w100_tg_info {int /*<<< orphan*/  (* change ) (struct w100fb_par*) ;} ;
struct TYPE_2__ {struct w100_tg_info* tg; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_hsync (struct w100fb_par*) ; 
 int /*<<< orphan*/  stub1 (struct w100fb_par*) ; 
 int /*<<< orphan*/  w100_init_clocks (struct w100fb_par*) ; 
 int /*<<< orphan*/  w100_init_graphic_engine (struct w100fb_par*) ; 
 int /*<<< orphan*/  w100_init_lcd (struct w100fb_par*) ; 
 int /*<<< orphan*/  w100_pwm_setup (struct w100fb_par*) ; 
 int /*<<< orphan*/  w100_set_dispregs (struct w100fb_par*) ; 
 int /*<<< orphan*/  w100_setup_memory (struct w100fb_par*) ; 
 int /*<<< orphan*/  w100_update_disable () ; 
 int /*<<< orphan*/  w100_update_enable () ; 
 int /*<<< orphan*/  w100_vsync () ; 
 int /*<<< orphan*/  w100fb_clear_screen (struct w100fb_par*) ; 

__attribute__((used)) static void w100fb_activate_var(struct w100fb_par *par)
{
	struct w100_tg_info *tg = par->mach->tg;

	w100_pwm_setup(par);
	w100_setup_memory(par);
	w100_init_clocks(par);
	w100fb_clear_screen(par);
	w100_vsync();

	w100_update_disable();
	w100_init_lcd(par);
	w100_set_dispregs(par);
	w100_update_enable();
	w100_init_graphic_engine(par);

	calc_hsync(par);

	if (!par->blanked && tg && tg->change)
		tg->change(par);
}