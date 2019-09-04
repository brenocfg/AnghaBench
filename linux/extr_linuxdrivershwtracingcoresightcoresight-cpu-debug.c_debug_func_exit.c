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
 int /*<<< orphan*/  atomic_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_debugfs_dir ; 
 int /*<<< orphan*/  debug_notifier ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic_notifier_list ; 

__attribute__((used)) static void debug_func_exit(void)
{
	atomic_notifier_chain_unregister(&panic_notifier_list,
					 &debug_notifier);
	debugfs_remove_recursive(debug_debugfs_dir);
}