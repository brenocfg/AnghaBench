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
struct virtqueue {size_t index; int /*<<< orphan*/  vdev; } ;
struct virtio_pci_vq_info {int /*<<< orphan*/  node; } ;
struct virtio_pci_device {int /*<<< orphan*/  (* del_vq ) (struct virtio_pci_vq_info*) ;int /*<<< orphan*/  lock; struct virtio_pci_vq_info** vqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct virtio_pci_vq_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct virtio_pci_vq_info*) ; 
 struct virtio_pci_device* to_vp_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vp_del_vq(struct virtqueue *vq)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vq->vdev);
	struct virtio_pci_vq_info *info = vp_dev->vqs[vq->index];
	unsigned long flags;

	spin_lock_irqsave(&vp_dev->lock, flags);
	list_del(&info->node);
	spin_unlock_irqrestore(&vp_dev->lock, flags);

	vp_dev->del_vq(info);
	kfree(info);
}