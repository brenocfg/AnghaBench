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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct bnad {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  bna_lock; TYPE_1__* rx_info; int /*<<< orphan*/  active_vlans; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  bna_rx_vlan_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bnad_vlan_rx_kill_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
	struct bnad *bnad = netdev_priv(netdev);
	unsigned long flags;

	if (!bnad->rx_info[0].rx)
		return 0;

	mutex_lock(&bnad->conf_mutex);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	clear_bit(vid, bnad->active_vlans);
	bna_rx_vlan_del(bnad->rx_info[0].rx, vid);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	mutex_unlock(&bnad->conf_mutex);

	return 0;
}