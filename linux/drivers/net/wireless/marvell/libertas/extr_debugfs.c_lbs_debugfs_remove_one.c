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
struct lbs_private {int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/ * debugfs_files; int /*<<< orphan*/  debugfs_debug; int /*<<< orphan*/  events_dir; int /*<<< orphan*/ * debugfs_events_files; int /*<<< orphan*/  regs_dir; int /*<<< orphan*/ * debugfs_regs_files; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_events_files ; 
 int /*<<< orphan*/  debugfs_files ; 
 int /*<<< orphan*/  debugfs_regs_files ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

void lbs_debugfs_remove_one(struct lbs_private *priv)
{
	int i;

	for(i=0; i<ARRAY_SIZE(debugfs_regs_files); i++)
		debugfs_remove(priv->debugfs_regs_files[i]);

	debugfs_remove(priv->regs_dir);

	for(i=0; i<ARRAY_SIZE(debugfs_events_files); i++)
		debugfs_remove(priv->debugfs_events_files[i]);

	debugfs_remove(priv->events_dir);
#ifdef PROC_DEBUG
	debugfs_remove(priv->debugfs_debug);
#endif
	for(i=0; i<ARRAY_SIZE(debugfs_files); i++)
		debugfs_remove(priv->debugfs_files[i]);
	debugfs_remove(priv->debugfs_dir);
}