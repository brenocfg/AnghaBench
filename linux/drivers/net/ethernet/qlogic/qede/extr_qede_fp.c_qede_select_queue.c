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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int num_tc; } ;
struct qede_dev {TYPE_1__ dev_info; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int QEDE_TSS_COUNT (struct qede_dev*) ; 
 int netdev_pick_tx (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 

u16 qede_select_queue(struct net_device *dev, struct sk_buff *skb,
		      struct net_device *sb_dev)
{
	struct qede_dev *edev = netdev_priv(dev);
	int total_txq;

	total_txq = QEDE_TSS_COUNT(edev) * edev->dev_info.num_tc;

	return QEDE_TSS_COUNT(edev) ?
		netdev_pick_tx(dev, skb, NULL) % total_txq :  0;
}