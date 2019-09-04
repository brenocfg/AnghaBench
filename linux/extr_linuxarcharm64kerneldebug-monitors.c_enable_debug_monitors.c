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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum dbg_active_el { ____Placeholder_dbg_active_el } dbg_active_el ;

/* Variables and functions */
 int DBG_ACTIVE_EL1 ; 
 int /*<<< orphan*/  DBG_MDSCR_KDE ; 
 int /*<<< orphan*/  DBG_MDSCR_MDE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_enabled ; 
 int /*<<< orphan*/  kde_ref_count ; 
 int /*<<< orphan*/  mde_ref_count ; 
 int /*<<< orphan*/  mdscr_read () ; 
 int /*<<< orphan*/  mdscr_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preemptible () ; 
 int this_cpu_inc_return (int /*<<< orphan*/ ) ; 

void enable_debug_monitors(enum dbg_active_el el)
{
	u32 mdscr, enable = 0;

	WARN_ON(preemptible());

	if (this_cpu_inc_return(mde_ref_count) == 1)
		enable = DBG_MDSCR_MDE;

	if (el == DBG_ACTIVE_EL1 &&
	    this_cpu_inc_return(kde_ref_count) == 1)
		enable |= DBG_MDSCR_KDE;

	if (enable && debug_enabled) {
		mdscr = mdscr_read();
		mdscr |= enable;
		mdscr_write(mdscr);
	}
}