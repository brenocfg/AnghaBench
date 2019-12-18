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
struct virtio_device {struct virtio_balloon* priv; } ;
struct TYPE_2__ {scalar_t__ inode; } ;
struct virtio_balloon {int stop_update; TYPE_1__ vb_dev_info; int /*<<< orphan*/  balloon_wq; int /*<<< orphan*/  report_free_page_work; int /*<<< orphan*/  update_balloon_stats_work; int /*<<< orphan*/  update_balloon_size_work; int /*<<< orphan*/  stop_update_lock; struct virtio_device* vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_BALLOON_F_DEFLATE_ON_OOM ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_F_FREE_PAGE_HINT ; 
 int /*<<< orphan*/  balloon_mnt ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (scalar_t__) ; 
 int /*<<< orphan*/  kern_unmount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct virtio_balloon*) ; 
 int /*<<< orphan*/  remove_common (struct virtio_balloon*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_balloon_unregister_shrinker (struct virtio_balloon*) ; 
 scalar_t__ virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtballoon_remove(struct virtio_device *vdev)
{
	struct virtio_balloon *vb = vdev->priv;

	if (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_DEFLATE_ON_OOM))
		virtio_balloon_unregister_shrinker(vb);
	spin_lock_irq(&vb->stop_update_lock);
	vb->stop_update = true;
	spin_unlock_irq(&vb->stop_update_lock);
	cancel_work_sync(&vb->update_balloon_size_work);
	cancel_work_sync(&vb->update_balloon_stats_work);

	if (virtio_has_feature(vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT)) {
		cancel_work_sync(&vb->report_free_page_work);
		destroy_workqueue(vb->balloon_wq);
	}

	remove_common(vb);
#ifdef CONFIG_BALLOON_COMPACTION
	if (vb->vb_dev_info.inode)
		iput(vb->vb_dev_info.inode);

	kern_unmount(balloon_mnt);
#endif
	kfree(vb);
}