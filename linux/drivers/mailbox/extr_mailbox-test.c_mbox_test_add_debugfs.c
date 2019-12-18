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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mbox_test_device {int /*<<< orphan*/  root_debugfs_dir; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct mbox_test_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_test_message_ops ; 
 int /*<<< orphan*/  mbox_test_signal_ops ; 

__attribute__((used)) static int mbox_test_add_debugfs(struct platform_device *pdev,
				 struct mbox_test_device *tdev)
{
	if (!debugfs_initialized())
		return 0;

	tdev->root_debugfs_dir = debugfs_create_dir(dev_name(&pdev->dev), NULL);
	if (!tdev->root_debugfs_dir) {
		dev_err(&pdev->dev, "Failed to create Mailbox debugfs\n");
		return -EINVAL;
	}

	debugfs_create_file("message", 0600, tdev->root_debugfs_dir,
			    tdev, &mbox_test_message_ops);

	debugfs_create_file("signal", 0200, tdev->root_debugfs_dir,
			    tdev, &mbox_test_signal_ops);

	return 0;
}