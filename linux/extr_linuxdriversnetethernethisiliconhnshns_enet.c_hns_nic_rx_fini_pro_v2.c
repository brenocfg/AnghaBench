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
struct hns_nic_ring_data {struct hnae_ring* ring; } ;
struct hnae_ring {TYPE_2__* q; scalar_t__ io_base; } ;
struct TYPE_4__ {TYPE_1__* handle; } ;
struct TYPE_3__ {scalar_t__ coal_adapt_en; } ;

/* Variables and functions */
 scalar_t__ RCB_REG_FBDNUM ; 
 int hns_coal_rx_bdnum (struct hnae_ring*) ; 
 int /*<<< orphan*/  hns_nic_adpt_coalesce (struct hns_nic_ring_data*) ; 
 int /*<<< orphan*/  hns_update_rx_rate (struct hnae_ring*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static bool hns_nic_rx_fini_pro_v2(struct hns_nic_ring_data *ring_data)
{
	struct hnae_ring *ring = ring_data->ring;
	int num;

	hns_update_rx_rate(ring);
	num = readl_relaxed(ring->io_base + RCB_REG_FBDNUM);

	if (num <= hns_coal_rx_bdnum(ring)) {
		if (ring->q->handle->coal_adapt_en)
			hns_nic_adpt_coalesce(ring_data);

		return true;
	}

	return false;
}