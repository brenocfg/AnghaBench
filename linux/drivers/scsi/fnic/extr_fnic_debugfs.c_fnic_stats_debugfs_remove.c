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
struct fnic {int /*<<< orphan*/ * fnic_stats_debugfs_host; int /*<<< orphan*/ * fnic_reset_debugfs_file; int /*<<< orphan*/ * fnic_stats_debugfs_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 

void fnic_stats_debugfs_remove(struct fnic *fnic)
{
	if (!fnic)
		return;

	debugfs_remove(fnic->fnic_stats_debugfs_file);
	fnic->fnic_stats_debugfs_file = NULL;

	debugfs_remove(fnic->fnic_reset_debugfs_file);
	fnic->fnic_reset_debugfs_file = NULL;

	debugfs_remove(fnic->fnic_stats_debugfs_host);
	fnic->fnic_stats_debugfs_host = NULL;
}