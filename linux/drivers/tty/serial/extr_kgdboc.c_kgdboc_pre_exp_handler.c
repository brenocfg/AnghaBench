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
struct TYPE_2__ {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_debug_enter (int /*<<< orphan*/ ) ; 
 int dbg_restore_graphics ; 
 size_t fg_console ; 
 int /*<<< orphan*/  ignore_console_lock_warning ; 
 int /*<<< orphan*/  kgdb_connected ; 
 scalar_t__ kgdboc_use_kms ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 TYPE_1__* vc_cons ; 

__attribute__((used)) static void kgdboc_pre_exp_handler(void)
{
	if (!dbg_restore_graphics && kgdboc_use_kms) {
		dbg_restore_graphics = 1;
		con_debug_enter(vc_cons[fg_console].d);
	}
	/* Increment the module count when the debugger is active */
	if (!kgdb_connected)
		try_module_get(THIS_MODULE);

	atomic_inc(&ignore_console_lock_warning);
}