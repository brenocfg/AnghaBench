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
struct fm10k_intfc {int /*<<< orphan*/ * dbg_intfc; } ;

/* Variables and functions */
 scalar_t__ dbg_root ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

void fm10k_dbg_intfc_exit(struct fm10k_intfc *interface)
{
	if (dbg_root)
		debugfs_remove_recursive(interface->dbg_intfc);
	interface->dbg_intfc = NULL;
}