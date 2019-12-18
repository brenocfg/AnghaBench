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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct can_frame {scalar_t__ can_dlc; } ;

/* Variables and functions */
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  at91_poll_err_frame (struct net_device*,struct can_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int at91_poll_err(struct net_device *dev, int quota, u32 reg_sr)
{
	struct sk_buff *skb;
	struct can_frame *cf;

	if (quota == 0)
		return 0;

	skb = alloc_can_err_skb(dev, &cf);
	if (unlikely(!skb))
		return 0;

	at91_poll_err_frame(dev, cf, reg_sr);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += cf->can_dlc;
	netif_receive_skb(skb);

	return 1;
}