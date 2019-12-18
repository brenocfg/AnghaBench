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
struct netdevsim_shared_dev {int /*<<< orphan*/  ddir; scalar_t__ refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct netdevsim_shared_dev*) ; 

void nsim_sdev_put(struct netdevsim_shared_dev *sdev)
{
	if (--sdev->refcnt)
		return;
	debugfs_remove_recursive(sdev->ddir);
	kfree(sdev);
}