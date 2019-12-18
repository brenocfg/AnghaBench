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
struct sk_buff {scalar_t__ len; } ;
struct net_device {scalar_t__ min_mtu; } ;

/* Variables and functions */
 int skb_put_padto (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int ibmvnic_xmit_workarounds(struct sk_buff *skb,
				    struct net_device *netdev)
{
	/* For some backing devices, mishandling of small packets
	 * can result in a loss of connection or TX stall. Device
	 * architects recommend that no packet should be smaller
	 * than the minimum MTU value provided to the driver, so
	 * pad any packets to that length
	 */
	if (skb->len < netdev->min_mtu)
		return skb_put_padto(skb, netdev->min_mtu);

	return 0;
}