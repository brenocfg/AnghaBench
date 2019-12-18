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
struct ixgbe_adapter {int /*<<< orphan*/ * ixgbe_dbg_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

void ixgbe_dbg_adapter_exit(struct ixgbe_adapter *adapter)
{
	debugfs_remove_recursive(adapter->ixgbe_dbg_adapter);
	adapter->ixgbe_dbg_adapter = NULL;
}