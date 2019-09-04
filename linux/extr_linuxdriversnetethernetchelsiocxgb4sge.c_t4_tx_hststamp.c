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
struct sk_buff {int dummy; } ;
struct port_info {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {scalar_t__ ptp_tx_skb; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_ptp_read_hwstamp (struct adapter*,struct port_info*) ; 
 int /*<<< orphan*/  is_t4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int t4_tx_hststamp(struct adapter *adapter, struct sk_buff *skb,
			  struct net_device *dev)
{
	struct port_info *pi = netdev_priv(dev);

	if (!is_t4(adapter->params.chip) && adapter->ptp_tx_skb) {
		cxgb4_ptp_read_hwstamp(adapter, pi);
		kfree_skb(skb);
		return 0;
	}
	return 1;
}