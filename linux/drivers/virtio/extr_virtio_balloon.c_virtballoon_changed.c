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
struct virtio_device {struct virtio_balloon* priv; } ;
struct virtio_balloon {int /*<<< orphan*/  stop_update_lock; int /*<<< orphan*/  update_balloon_size_work; int /*<<< orphan*/  stop_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_freezable_wq ; 
 int /*<<< orphan*/  virtio_balloon_queue_free_page_work (struct virtio_balloon*) ; 

__attribute__((used)) static void virtballoon_changed(struct virtio_device *vdev)
{
	struct virtio_balloon *vb = vdev->priv;
	unsigned long flags;

	spin_lock_irqsave(&vb->stop_update_lock, flags);
	if (!vb->stop_update) {
		queue_work(system_freezable_wq,
			   &vb->update_balloon_size_work);
		virtio_balloon_queue_free_page_work(vb);
	}
	spin_unlock_irqrestore(&vb->stop_update_lock, flags);
}