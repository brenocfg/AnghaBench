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
typedef  size_t u32 ;
struct hns3_nic_priv {TYPE_1__* ring_data; } ;
struct hns3_enet_ring {int dummy; } ;
struct TYPE_2__ {struct hns3_enet_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_clean_tx_ring (struct hns3_enet_ring*) ; 

__attribute__((used)) static void hns3_lb_clear_tx_ring(struct hns3_nic_priv *priv, u32 start_ringid,
				  u32 end_ringid, u32 budget)
{
	u32 i;

	for (i = start_ringid; i <= end_ringid; i++) {
		struct hns3_enet_ring *ring = priv->ring_data[i].ring;

		hns3_clean_tx_ring(ring);
	}
}