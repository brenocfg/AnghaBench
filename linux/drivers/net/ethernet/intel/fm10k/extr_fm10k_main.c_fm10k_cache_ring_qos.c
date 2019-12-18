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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct fm10k_intfc {TYPE_3__** rx_ring; TYPE_2__** tx_ring; TYPE_1__* ring_feature; struct net_device* netdev; } ;
struct TYPE_6__ {int reg_idx; int qos_pc; } ;
struct TYPE_5__ {int reg_idx; int qos_pc; } ;
struct TYPE_4__ {int indices; scalar_t__ mask; } ;

/* Variables and functions */
 size_t RING_F_QOS ; 
 size_t RING_F_RSS ; 
 int netdev_get_num_tc (struct net_device*) ; 

__attribute__((used)) static bool fm10k_cache_ring_qos(struct fm10k_intfc *interface)
{
	struct net_device *dev = interface->netdev;
	int pc, offset, rss_i, i;
	u16 pc_stride = interface->ring_feature[RING_F_QOS].mask + 1;
	u8 num_pcs = netdev_get_num_tc(dev);

	if (num_pcs <= 1)
		return false;

	rss_i = interface->ring_feature[RING_F_RSS].indices;

	for (pc = 0, offset = 0; pc < num_pcs; pc++, offset += rss_i) {
		int q_idx = pc;

		for (i = 0; i < rss_i; i++) {
			interface->tx_ring[offset + i]->reg_idx = q_idx;
			interface->tx_ring[offset + i]->qos_pc = pc;
			interface->rx_ring[offset + i]->reg_idx = q_idx;
			interface->rx_ring[offset + i]->qos_pc = pc;
			q_idx += pc_stride;
		}
	}

	return true;
}