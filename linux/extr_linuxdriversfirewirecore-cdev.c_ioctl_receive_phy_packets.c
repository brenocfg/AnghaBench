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
struct fw_cdev_receive_phy_packets {int /*<<< orphan*/  closure; } ;
union ioctl_arg {struct fw_cdev_receive_phy_packets receive_phy_packets; } ;
struct fw_card {int /*<<< orphan*/  lock; int /*<<< orphan*/  phy_receiver_list; } ;
struct client {int /*<<< orphan*/  phy_receiver_closure; int /*<<< orphan*/  phy_receiver_link; TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_local; struct fw_card* card; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioctl_receive_phy_packets(struct client *client, union ioctl_arg *arg)
{
	struct fw_cdev_receive_phy_packets *a = &arg->receive_phy_packets;
	struct fw_card *card = client->device->card;

	/* Access policy: Allow this ioctl only on local nodes' device files. */
	if (!client->device->is_local)
		return -ENOSYS;

	spin_lock_irq(&card->lock);

	list_move_tail(&client->phy_receiver_link, &card->phy_receiver_list);
	client->phy_receiver_closure = a->closure;

	spin_unlock_irq(&card->lock);

	return 0;
}