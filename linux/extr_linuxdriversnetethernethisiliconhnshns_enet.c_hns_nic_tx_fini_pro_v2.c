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
struct hns_nic_ring_data {struct hnae_ring* ring; } ;
struct hnae_ring {int next_to_clean; scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ RCB_REG_HEAD ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static bool hns_nic_tx_fini_pro_v2(struct hns_nic_ring_data *ring_data)
{
	struct hnae_ring *ring = ring_data->ring;
	int head = readl_relaxed(ring->io_base + RCB_REG_HEAD);

	if (head == ring->next_to_clean)
		return true;
	else
		return false;
}