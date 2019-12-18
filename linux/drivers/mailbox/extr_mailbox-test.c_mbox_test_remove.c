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
struct platform_device {int dummy; } ;
struct mbox_test_device {scalar_t__ rx_channel; scalar_t__ tx_channel; int /*<<< orphan*/  root_debugfs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_free_channel (scalar_t__) ; 
 struct mbox_test_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mbox_test_remove(struct platform_device *pdev)
{
	struct mbox_test_device *tdev = platform_get_drvdata(pdev);

	debugfs_remove_recursive(tdev->root_debugfs_dir);

	if (tdev->tx_channel)
		mbox_free_channel(tdev->tx_channel);
	if (tdev->rx_channel)
		mbox_free_channel(tdev->rx_channel);

	return 0;
}