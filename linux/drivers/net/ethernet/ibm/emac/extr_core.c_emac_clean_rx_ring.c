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
struct emac_instance {int /*<<< orphan*/ * rx_sg_skb; TYPE_1__* rx_desc; int /*<<< orphan*/ ** rx_skb; } ;
struct TYPE_2__ {scalar_t__ data_ptr; scalar_t__ ctrl; } ;

/* Variables and functions */
 int NUM_RX_BUFF ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emac_clean_rx_ring(struct emac_instance *dev)
{
	int i;

	for (i = 0; i < NUM_RX_BUFF; ++i)
		if (dev->rx_skb[i]) {
			dev->rx_desc[i].ctrl = 0;
			dev_kfree_skb(dev->rx_skb[i]);
			dev->rx_skb[i] = NULL;
			dev->rx_desc[i].data_ptr = 0;
		}

	if (dev->rx_sg_skb) {
		dev_kfree_skb(dev->rx_sg_skb);
		dev->rx_sg_skb = NULL;
	}
}