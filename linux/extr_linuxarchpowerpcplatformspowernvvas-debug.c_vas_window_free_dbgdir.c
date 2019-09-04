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
struct vas_window {int /*<<< orphan*/ * dbgname; int /*<<< orphan*/ * dbgdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void vas_window_free_dbgdir(struct vas_window *window)
{
	if (window->dbgdir) {
		debugfs_remove_recursive(window->dbgdir);
		kfree(window->dbgname);
		window->dbgdir = NULL;
		window->dbgname = NULL;
	}
}