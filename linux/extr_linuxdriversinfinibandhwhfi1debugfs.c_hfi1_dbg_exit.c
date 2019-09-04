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
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hfi1_dbg_root ; 

void hfi1_dbg_exit(void)
{
	debugfs_remove_recursive(hfi1_dbg_root);
	hfi1_dbg_root = NULL;
}