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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int /*<<< orphan*/  bad_req_id; } ;
struct ena_ring {scalar_t__ ring_size; TYPE_2__* adapter; int /*<<< orphan*/  syncp; TYPE_1__ rx_stats; int /*<<< orphan*/  netdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_reason; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_INV_RX_REQ_ID ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netif_err (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int validate_rx_req_id(struct ena_ring *rx_ring, u16 req_id)
{
	if (likely(req_id < rx_ring->ring_size))
		return 0;

	netif_err(rx_ring->adapter, rx_err, rx_ring->netdev,
		  "Invalid rx req_id: %hu\n", req_id);

	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->rx_stats.bad_req_id++;
	u64_stats_update_end(&rx_ring->syncp);

	/* Trigger device reset */
	rx_ring->adapter->reset_reason = ENA_REGS_RESET_INV_RX_REQ_ID;
	set_bit(ENA_FLAG_TRIGGER_RESET, &rx_ring->adapter->flags);
	return -EFAULT;
}