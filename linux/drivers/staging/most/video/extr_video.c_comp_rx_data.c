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
struct most_video_dev {int /*<<< orphan*/  wait_data; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  pending_mbos; int /*<<< orphan*/  mute; } ;
struct mbo {int /*<<< orphan*/  list; int /*<<< orphan*/  hdm_channel_id; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int EIO ; 
 struct most_video_dev* get_comp_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int comp_rx_data(struct mbo *mbo)
{
	unsigned long flags;
	struct most_video_dev *mdev =
		get_comp_dev(mbo->ifp, mbo->hdm_channel_id);

	if (!mdev)
		return -EIO;

	spin_lock_irqsave(&mdev->list_lock, flags);
	if (unlikely(mdev->mute)) {
		spin_unlock_irqrestore(&mdev->list_lock, flags);
		return -EIO;
	}

	list_add_tail(&mbo->list, &mdev->pending_mbos);
	spin_unlock_irqrestore(&mdev->list_lock, flags);
	wake_up_interruptible(&mdev->wait_data);
	return 0;
}