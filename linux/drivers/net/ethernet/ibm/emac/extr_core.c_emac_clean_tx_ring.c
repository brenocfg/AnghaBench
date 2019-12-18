#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct emac_instance {TYPE_2__* tx_desc; TYPE_1__ estats; int /*<<< orphan*/ ** tx_skb; } ;
struct TYPE_4__ {int ctrl; scalar_t__ data_ptr; } ;

/* Variables and functions */
 int MAL_TX_CTRL_READY ; 
 int NUM_TX_BUFF ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emac_clean_tx_ring(struct emac_instance *dev)
{
	int i;

	for (i = 0; i < NUM_TX_BUFF; ++i) {
		if (dev->tx_skb[i]) {
			dev_kfree_skb(dev->tx_skb[i]);
			dev->tx_skb[i] = NULL;
			if (dev->tx_desc[i].ctrl & MAL_TX_CTRL_READY)
				++dev->estats.tx_dropped;
		}
		dev->tx_desc[i].ctrl = 0;
		dev->tx_desc[i].data_ptr = 0;
	}
}