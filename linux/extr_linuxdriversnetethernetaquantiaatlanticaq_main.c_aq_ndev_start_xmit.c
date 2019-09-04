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
struct net_device {int dummy; } ;
struct aq_nic_s {int dummy; } ;

/* Variables and functions */
 int aq_nic_xmit (struct aq_nic_s*,struct sk_buff*) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int aq_ndev_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct aq_nic_s *aq_nic = netdev_priv(ndev);

	return aq_nic_xmit(aq_nic, skb);
}