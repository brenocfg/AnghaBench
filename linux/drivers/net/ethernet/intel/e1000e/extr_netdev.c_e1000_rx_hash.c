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
struct net_device {int features; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void e1000_rx_hash(struct net_device *netdev, __le32 rss,
				 struct sk_buff *skb)
{
	if (netdev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, le32_to_cpu(rss), PKT_HASH_TYPE_L3);
}