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
typedef  int u16 ;
struct sk_buff {scalar_t__ protocol; int priority; } ;
struct net_device {int real_num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_FCOE ; 
 int VLAN_PRIO_MASK ; 
 int VLAN_PRIO_SHIFT ; 
 scalar_t__ cxgb4_dcb_enabled (struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_kdump_kernel () ; 
 scalar_t__ net_ratelimit () ; 
 int netdev_pick_tx (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 scalar_t__ select_queue ; 
 int skb_get_rx_queue (struct sk_buff*) ; 
 scalar_t__ skb_rx_queue_recorded (struct sk_buff*) ; 
 int smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 
 int vlan_get_tag (struct sk_buff*,int*) ; 

__attribute__((used)) static u16 cxgb_select_queue(struct net_device *dev, struct sk_buff *skb,
			     struct net_device *sb_dev)
{
	int txq;

#ifdef CONFIG_CHELSIO_T4_DCB
	/* If a Data Center Bridging has been successfully negotiated on this
	 * link then we'll use the skb's priority to map it to a TX Queue.
	 * The skb's priority is determined via the VLAN Tag Priority Code
	 * Point field.
	 */
	if (cxgb4_dcb_enabled(dev) && !is_kdump_kernel()) {
		u16 vlan_tci;
		int err;

		err = vlan_get_tag(skb, &vlan_tci);
		if (unlikely(err)) {
			if (net_ratelimit())
				netdev_warn(dev,
					    "TX Packet without VLAN Tag on DCB Link\n");
			txq = 0;
		} else {
			txq = (vlan_tci & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
#ifdef CONFIG_CHELSIO_T4_FCOE
			if (skb->protocol == htons(ETH_P_FCOE))
				txq = skb->priority & 0x7;
#endif /* CONFIG_CHELSIO_T4_FCOE */
		}
		return txq;
	}
#endif /* CONFIG_CHELSIO_T4_DCB */

	if (select_queue) {
		txq = (skb_rx_queue_recorded(skb)
			? skb_get_rx_queue(skb)
			: smp_processor_id());

		while (unlikely(txq >= dev->real_num_tx_queues))
			txq -= dev->real_num_tx_queues;

		return txq;
	}

	return netdev_pick_tx(dev, skb, NULL) % dev->real_num_tx_queues;
}