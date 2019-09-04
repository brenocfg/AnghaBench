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
struct dchannel {scalar_t__ tx_idx; int /*<<< orphan*/  hw; TYPE_1__* tx_skb; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (TYPE_1__*) ; 
 scalar_t__ get_next_dframe (struct dchannel*) ; 
 int /*<<< orphan*/  hfcpci_fill_dfifo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
tx_dirq(struct dchannel *dch)
{
	if (dch->tx_skb && dch->tx_idx < dch->tx_skb->len)
		hfcpci_fill_dfifo(dch->hw);
	else {
		if (dch->tx_skb)
			dev_kfree_skb(dch->tx_skb);
		if (get_next_dframe(dch))
			hfcpci_fill_dfifo(dch->hw);
	}
}