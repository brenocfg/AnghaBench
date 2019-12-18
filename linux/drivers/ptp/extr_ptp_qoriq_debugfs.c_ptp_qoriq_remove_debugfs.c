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
struct ptp_qoriq {int /*<<< orphan*/ * debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

void ptp_qoriq_remove_debugfs(struct ptp_qoriq *ptp_qoriq)
{
	debugfs_remove_recursive(ptp_qoriq->debugfs_root);
	ptp_qoriq->debugfs_root = NULL;
}