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
struct vfio_ap_queue {int /*<<< orphan*/  apqn; } ;
struct ap_device {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 struct vfio_ap_queue* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vfio_ap_queue*) ; 
 TYPE_1__* matrix_dev ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_ap_irq_disable (struct vfio_ap_queue*) ; 
 int /*<<< orphan*/  vfio_ap_mdev_reset_queue (int,int,int) ; 

__attribute__((used)) static void vfio_ap_queue_dev_remove(struct ap_device *apdev)
{
	struct vfio_ap_queue *q;
	int apid, apqi;

	mutex_lock(&matrix_dev->lock);
	q = dev_get_drvdata(&apdev->device);
	dev_set_drvdata(&apdev->device, NULL);
	apid = AP_QID_CARD(q->apqn);
	apqi = AP_QID_QUEUE(q->apqn);
	vfio_ap_mdev_reset_queue(apid, apqi, 1);
	vfio_ap_irq_disable(q);
	kfree(q);
	mutex_unlock(&matrix_dev->lock);
}