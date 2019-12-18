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
struct most_interface {int num_channels; } ;
struct most_dev {int* is_channel_healthy; int* padding_active; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  poll_work_obj; int /*<<< orphan*/  link_stat_timer; TYPE_3__* conf; int /*<<< orphan*/ * busy_urbs; TYPE_2__* clear_work; int /*<<< orphan*/ * channel_lock; TYPE_1__* usb_device; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_6__ {scalar_t__ data_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  ws; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ECHRNG ; 
 int EIO ; 
 scalar_t__ MOST_CH_ASYNC ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct most_dev* to_mdev (struct most_interface*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdm_poison_channel(struct most_interface *iface, int channel)
{
	struct most_dev *mdev = to_mdev(iface);
	unsigned long flags;
	spinlock_t *lock; /* temp. lock */

	if (unlikely(!iface)) {
		dev_warn(&mdev->usb_device->dev, "Poison: Bad interface.\n");
		return -EIO;
	}
	if (unlikely(channel < 0 || channel >= iface->num_channels)) {
		dev_warn(&mdev->usb_device->dev, "Channel ID out of range.\n");
		return -ECHRNG;
	}

	lock = mdev->channel_lock + channel;
	spin_lock_irqsave(lock, flags);
	mdev->is_channel_healthy[channel] = false;
	spin_unlock_irqrestore(lock, flags);

	cancel_work_sync(&mdev->clear_work[channel].ws);

	mutex_lock(&mdev->io_mutex);
	usb_kill_anchored_urbs(&mdev->busy_urbs[channel]);
	if (mdev->padding_active[channel])
		mdev->padding_active[channel] = false;

	if (mdev->conf[channel].data_type == MOST_CH_ASYNC) {
		del_timer_sync(&mdev->link_stat_timer);
		cancel_work_sync(&mdev->poll_work_obj);
	}
	mutex_unlock(&mdev->io_mutex);
	return 0;
}