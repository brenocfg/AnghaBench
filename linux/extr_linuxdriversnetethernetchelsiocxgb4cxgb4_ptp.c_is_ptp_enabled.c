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
struct sk_buff {int dummy; } ;
struct port_info {scalar_t__ ptp_enable; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ cxgb4_ptp_is_ptp_tx (struct sk_buff*) ; 
 scalar_t__ cxgb4_xmit_with_hwtstamp (struct sk_buff*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

bool is_ptp_enabled(struct sk_buff *skb, struct net_device *dev)
{
	struct port_info *pi;

	pi = netdev_priv(dev);
	return (pi->ptp_enable && cxgb4_xmit_with_hwtstamp(skb) &&
		cxgb4_ptp_is_ptp_tx(skb));
}