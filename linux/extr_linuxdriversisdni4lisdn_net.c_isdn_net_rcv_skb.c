#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  dialstate; } ;
typedef  TYPE_1__ isdn_net_local ;
struct TYPE_5__ {int /*<<< orphan*/  dev; TYPE_1__* local; } ;
typedef  TYPE_2__ isdn_net_dev ;
struct TYPE_6__ {TYPE_2__** rx_netdev; } ;

/* Variables and functions */
 int ISDN_NET_CONNECTED ; 
 TYPE_3__* dev ; 
 int /*<<< orphan*/  isdn_net_receive (int /*<<< orphan*/ ,struct sk_buff*) ; 

int
isdn_net_rcv_skb(int idx, struct sk_buff *skb)
{
	isdn_net_dev *p = dev->rx_netdev[idx];

	if (p) {
		isdn_net_local *lp = p->local;
		if ((lp->flags & ISDN_NET_CONNECTED) &&
		    (!lp->dialstate)) {
			isdn_net_receive(p->dev, skb);
			return 1;
		}
	}
	return 0;
}