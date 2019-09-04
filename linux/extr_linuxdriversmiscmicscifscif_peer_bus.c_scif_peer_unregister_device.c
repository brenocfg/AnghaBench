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
struct scif_peer_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  dnode; } ;
struct scif_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  spdev; int /*<<< orphan*/  peer_add_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  conflock; int /*<<< orphan*/  total; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct scif_peer_dev* rcu_dereference (int /*<<< orphan*/ ) ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

int scif_peer_unregister_device(struct scif_dev *scifdev)
{
	struct scif_peer_dev *spdev;

	mutex_lock(&scifdev->lock);
	/* Flush work to ensure device register is complete */
	flush_work(&scifdev->peer_add_work);

	/*
	 * Continue holding scifdev->lock since theoretically unregister_device
	 * can be called simultaneously from multiple threads
	 */
	spdev = rcu_dereference(scifdev->spdev);
	if (!spdev) {
		mutex_unlock(&scifdev->lock);
		return -ENODEV;
	}

	RCU_INIT_POINTER(scifdev->spdev, NULL);
	synchronize_rcu();
	mutex_unlock(&scifdev->lock);

	dev_dbg(&spdev->dev, "Removing peer dnode %d\n", spdev->dnode);
	device_unregister(&spdev->dev);

	mutex_lock(&scif_info.conflock);
	scif_info.total--;
	mutex_unlock(&scif_info.conflock);
	return 0;
}