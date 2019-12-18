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
struct tb_cm {int hotplug_active; } ;
struct tb {int /*<<< orphan*/  root_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  tb_dbg (struct tb*,char*) ; 
 struct tb_cm* tb_priv (struct tb*) ; 
 int /*<<< orphan*/  tb_switch_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb_suspend_noirq(struct tb *tb)
{
	struct tb_cm *tcm = tb_priv(tb);

	tb_dbg(tb, "suspending...\n");
	tb_switch_suspend(tb->root_switch);
	tcm->hotplug_active = false; /* signal tb_handle_hotplug to quit */
	tb_dbg(tb, "suspend finished\n");

	return 0;
}