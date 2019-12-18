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
struct vop_vdev {int /*<<< orphan*/  virtio_bh_work; int /*<<< orphan*/  virtio_db; struct vop_device* vpdev; } ;
struct vop_device {TYPE_1__* hw_ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack_interrupt ) (struct vop_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vop_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t _vop_virtio_intr_handler(int irq, void *data)
{
	struct vop_vdev *vdev = data;
	struct vop_device *vpdev = vdev->vpdev;

	vpdev->hw_ops->ack_interrupt(vpdev, vdev->virtio_db);
	schedule_work(&vdev->virtio_bh_work);
	return IRQ_HANDLED;
}