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
struct mvpp2 {int /*<<< orphan*/  dbgfs_entries; int /*<<< orphan*/  dbgfs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void mvpp2_dbgfs_cleanup(struct mvpp2 *priv)
{
	debugfs_remove_recursive(priv->dbgfs_dir);

	kfree(priv->dbgfs_entries);
}