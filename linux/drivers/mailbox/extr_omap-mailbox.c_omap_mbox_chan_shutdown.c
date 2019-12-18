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
struct omap_mbox_device {int /*<<< orphan*/  cfg_lock; int /*<<< orphan*/  dev; } ;
struct omap_mbox {struct omap_mbox_device* parent; } ;
struct mbox_chan {int dummy; } ;

/* Variables and functions */
 struct omap_mbox* mbox_chan_to_omap_mbox (struct mbox_chan*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_mbox_fini (struct omap_mbox*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_mbox_chan_shutdown(struct mbox_chan *chan)
{
	struct omap_mbox *mbox = mbox_chan_to_omap_mbox(chan);
	struct omap_mbox_device *mdev = mbox->parent;

	mutex_lock(&mdev->cfg_lock);
	omap_mbox_fini(mbox);
	pm_runtime_put_sync(mdev->dev);
	mutex_unlock(&mdev->cfg_lock);
}