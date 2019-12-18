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

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_debug_leave () ; 
 scalar_t__ dbg_restore_graphics ; 
 int /*<<< orphan*/  ignore_console_lock_warning ; 
 int /*<<< orphan*/  kgdb_connected ; 
 int /*<<< orphan*/  kgdboc_restore_input () ; 
 scalar_t__ kgdboc_use_kms ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kgdboc_post_exp_handler(void)
{
	atomic_dec(&ignore_console_lock_warning);

	/* decrement the module count when the debugger detaches */
	if (!kgdb_connected)
		module_put(THIS_MODULE);
	if (kgdboc_use_kms && dbg_restore_graphics) {
		dbg_restore_graphics = 0;
		con_debug_leave();
	}
	kgdboc_restore_input();
}