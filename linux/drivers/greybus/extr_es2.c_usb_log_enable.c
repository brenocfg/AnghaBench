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
struct es2_ap_dev {int /*<<< orphan*/  apb_log_dentry; int /*<<< orphan*/  apb_log_task; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apb_log_fops ; 
 int /*<<< orphan*/  apb_log_poll ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct es2_ap_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_debugfs_get () ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct es2_ap_dev*,char*) ; 

__attribute__((used)) static void usb_log_enable(struct es2_ap_dev *es2)
{
	if (!IS_ERR_OR_NULL(es2->apb_log_task))
		return;

	/* get log from APB1 */
	es2->apb_log_task = kthread_run(apb_log_poll, es2, "apb_log");
	if (IS_ERR(es2->apb_log_task))
		return;
	/* XXX We will need to rename this per APB */
	es2->apb_log_dentry = debugfs_create_file("apb_log", 0444,
						  gb_debugfs_get(), es2,
						  &apb_log_fops);
}