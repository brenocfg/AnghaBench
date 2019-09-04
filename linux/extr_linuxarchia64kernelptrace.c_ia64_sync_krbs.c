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
 int /*<<< orphan*/  TIF_RESTORE_RSE ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  do_sync_rbs ; 
 int /*<<< orphan*/  ia64_sync_kernel_rbs ; 
 int /*<<< orphan*/  unw_init_running (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ia64_sync_krbs(void)
{
	clear_tsk_thread_flag(current, TIF_RESTORE_RSE);

	unw_init_running(do_sync_rbs, ia64_sync_kernel_rbs);
}