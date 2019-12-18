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
struct snic {int /*<<< orphan*/ * stats_host; int /*<<< orphan*/ * reset_stats_file; int /*<<< orphan*/ * stats_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 

void
snic_stats_debugfs_remove(struct snic *snic)
{
	debugfs_remove(snic->stats_file);
	snic->stats_file = NULL;

	debugfs_remove(snic->reset_stats_file);
	snic->reset_stats_file = NULL;

	debugfs_remove(snic->stats_host);
	snic->stats_host = NULL;
}