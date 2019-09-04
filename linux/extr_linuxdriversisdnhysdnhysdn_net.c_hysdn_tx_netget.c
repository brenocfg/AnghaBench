#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_local {size_t out_idx; struct sk_buff** skbs; int /*<<< orphan*/  sk_count; } ;
struct TYPE_3__ {struct net_local* netif; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */

struct sk_buff *
hysdn_tx_netget(hysdn_card *card)
{
	struct net_local *lp = card->netif;

	if (!lp)
		return (NULL);	/* non existing device */

	if (!lp->sk_count)
		return (NULL);	/* nothing available */

	return (lp->skbs[lp->out_idx]);		/* next packet to send */
}