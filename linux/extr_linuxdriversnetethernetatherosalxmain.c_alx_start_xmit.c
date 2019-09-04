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
struct alx_priv {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  alx_start_xmit_ring (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_tx_queue_mapping (struct alx_priv*,struct sk_buff*) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t alx_start_xmit(struct sk_buff *skb,
				  struct net_device *netdev)
{
	struct alx_priv *alx = netdev_priv(netdev);
	return alx_start_xmit_ring(skb, alx_tx_queue_mapping(alx, skb));
}