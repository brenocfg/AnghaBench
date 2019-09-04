#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ notifier_call; } ;
struct ti_sci_info {int /*<<< orphan*/  chan_rx; int /*<<< orphan*/  chan_tx; int /*<<< orphan*/  node; scalar_t__ users; TYPE_1__ nb; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 
 struct ti_sci_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ti_sci_debugfs_destroy (struct platform_device*,struct ti_sci_info*) ; 
 int /*<<< orphan*/  ti_sci_list_mutex ; 
 int /*<<< orphan*/  unregister_restart_handler (TYPE_1__*) ; 

__attribute__((used)) static int ti_sci_remove(struct platform_device *pdev)
{
	struct ti_sci_info *info;
	struct device *dev = &pdev->dev;
	int ret = 0;

	of_platform_depopulate(dev);

	info = platform_get_drvdata(pdev);

	if (info->nb.notifier_call)
		unregister_restart_handler(&info->nb);

	mutex_lock(&ti_sci_list_mutex);
	if (info->users)
		ret = -EBUSY;
	else
		list_del(&info->node);
	mutex_unlock(&ti_sci_list_mutex);

	if (!ret) {
		ti_sci_debugfs_destroy(pdev, info);

		/* Safe to free channels since no more users */
		mbox_free_channel(info->chan_tx);
		mbox_free_channel(info->chan_rx);
	}

	return ret;
}