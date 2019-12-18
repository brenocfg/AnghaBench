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
struct sky2_port {unsigned int rx_pending; TYPE_1__* hw; struct rx_ring_info* rx_ring; scalar_t__ rx_le; } ;
struct rx_ring_info {int /*<<< orphan*/ * skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_LE_BYTES ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_rx_unmap_skb (int /*<<< orphan*/ ,struct rx_ring_info*) ; 

__attribute__((used)) static void sky2_rx_clean(struct sky2_port *sky2)
{
	unsigned i;

	if (sky2->rx_le)
		memset(sky2->rx_le, 0, RX_LE_BYTES);

	for (i = 0; i < sky2->rx_pending; i++) {
		struct rx_ring_info *re = sky2->rx_ring + i;

		if (re->skb) {
			sky2_rx_unmap_skb(sky2->hw->pdev, re);
			kfree_skb(re->skb);
			re->skb = NULL;
		}
	}
}