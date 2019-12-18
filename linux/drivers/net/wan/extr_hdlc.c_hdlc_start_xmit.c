#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* xmit ) (struct sk_buff*,struct net_device*) ;TYPE_1__* proto; } ;
typedef  TYPE_2__ hdlc_device ;
struct TYPE_4__ {int /*<<< orphan*/  (* xmit ) (struct sk_buff*,struct net_device*) ;} ;

/* Variables and functions */
 TYPE_2__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct sk_buff*,struct net_device*) ; 

netdev_tx_t hdlc_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);

	if (hdlc->proto->xmit)
		return hdlc->proto->xmit(skb, dev);

	return hdlc->xmit(skb, dev); /* call hardware driver directly */
}