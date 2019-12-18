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
struct scif_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  peer_add_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int scif_peer_initialize_device (struct scif_dev*) ; 

void scif_peer_register_device(struct scif_dev *scifdev)
{
	int ret;

	mutex_lock(&scifdev->lock);
	ret = scif_peer_initialize_device(scifdev);
	if (ret)
		goto exit;
	schedule_work(&scifdev->peer_add_work);
exit:
	mutex_unlock(&scifdev->lock);
}