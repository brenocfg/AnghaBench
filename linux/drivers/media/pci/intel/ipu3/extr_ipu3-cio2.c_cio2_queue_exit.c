#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  entity; } ;
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct cio2_queue {int /*<<< orphan*/  lock; TYPE_3__ subdev; int /*<<< orphan*/  vbq; TYPE_2__ vdev; } ;
struct cio2_device {TYPE_1__* pci_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cio2_fbpt_exit (struct cio2_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (TYPE_3__*) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_2__*) ; 

__attribute__((used)) static void cio2_queue_exit(struct cio2_device *cio2, struct cio2_queue *q)
{
	video_unregister_device(&q->vdev);
	media_entity_cleanup(&q->vdev.entity);
	vb2_queue_release(&q->vbq);
	v4l2_device_unregister_subdev(&q->subdev);
	media_entity_cleanup(&q->subdev.entity);
	cio2_fbpt_exit(q, &cio2->pci_dev->dev);
	mutex_destroy(&q->lock);
}