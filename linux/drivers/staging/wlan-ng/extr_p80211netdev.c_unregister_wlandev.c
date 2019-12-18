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
struct wlandevice {int /*<<< orphan*/  nsd_rxq; int /*<<< orphan*/  netdev; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

int unregister_wlandev(struct wlandevice *wlandev)
{
	struct sk_buff *skb;

	unregister_netdev(wlandev->netdev);

	/* Now to clean out the rx queue */
	while ((skb = skb_dequeue(&wlandev->nsd_rxq)))
		dev_kfree_skb(skb);

	return 0;
}