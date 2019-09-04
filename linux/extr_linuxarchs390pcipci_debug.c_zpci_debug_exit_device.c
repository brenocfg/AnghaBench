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
struct zpci_dev {int /*<<< orphan*/  debugfs_dev; int /*<<< orphan*/  debugfs_perf; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

void zpci_debug_exit_device(struct zpci_dev *zdev)
{
	debugfs_remove(zdev->debugfs_perf);
	debugfs_remove(zdev->debugfs_dev);
}