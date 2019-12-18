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
struct es2_ap_dev {int /*<<< orphan*/ * apb_log_task; int /*<<< orphan*/ * apb_log_dentry; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_log_disable(struct es2_ap_dev *es2)
{
	if (IS_ERR_OR_NULL(es2->apb_log_task))
		return;

	debugfs_remove(es2->apb_log_dentry);
	es2->apb_log_dentry = NULL;

	kthread_stop(es2->apb_log_task);
	es2->apb_log_task = NULL;
}