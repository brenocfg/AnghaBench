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
typedef  size_t u16 ;
struct ena_tx_buffer {int skb; } ;
struct TYPE_3__ {int /*<<< orphan*/  bad_req_id; } ;
struct ena_ring {size_t ring_size; TYPE_2__* adapter; int /*<<< orphan*/  syncp; TYPE_1__ tx_stats; int /*<<< orphan*/  netdev; struct ena_tx_buffer* tx_buffer_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_reason; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_INV_TX_REQ_ID ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netif_err (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_done ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int validate_tx_req_id(struct ena_ring *tx_ring, u16 req_id)
{
	struct ena_tx_buffer *tx_info = NULL;

	if (likely(req_id < tx_ring->ring_size)) {
		tx_info = &tx_ring->tx_buffer_info[req_id];
		if (likely(tx_info->skb))
			return 0;
	}

	if (tx_info)
		netif_err(tx_ring->adapter, tx_done, tx_ring->netdev,
			  "tx_info doesn't have valid skb\n");
	else
		netif_err(tx_ring->adapter, tx_done, tx_ring->netdev,
			  "Invalid req_id: %hu\n", req_id);

	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->tx_stats.bad_req_id++;
	u64_stats_update_end(&tx_ring->syncp);

	/* Trigger device reset */
	tx_ring->adapter->reset_reason = ENA_REGS_RESET_INV_TX_REQ_ID;
	set_bit(ENA_FLAG_TRIGGER_RESET, &tx_ring->adapter->flags);
	return -EFAULT;
}