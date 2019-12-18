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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int tx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAVB_BE ; 
 int /*<<< orphan*/  RAVB_NC ; 
 int SKBTX_HW_TSTAMP ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static u16 ravb_select_queue(struct net_device *ndev, struct sk_buff *skb,
			     struct net_device *sb_dev)
{
	/* If skb needs TX timestamp, it is handled in network control queue */
	return (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) ? RAVB_NC :
							       RAVB_BE;

}