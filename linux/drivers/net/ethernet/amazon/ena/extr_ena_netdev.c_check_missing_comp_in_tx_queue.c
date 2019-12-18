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
typedef  scalar_t__ u32 ;
struct ena_tx_buffer {unsigned long last_jiffies; int print_once; } ;
struct TYPE_2__ {scalar_t__ missed_tx; } ;
struct ena_ring {int ring_size; int /*<<< orphan*/  syncp; TYPE_1__ tx_stats; int /*<<< orphan*/  qid; int /*<<< orphan*/  first_interrupt; struct ena_tx_buffer* tx_buffer_info; } ;
struct ena_adapter {int missing_tx_completion_to; int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_reason; scalar_t__ missing_tx_completion_threshold; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_MISS_INTERRUPT ; 
 int /*<<< orphan*/  ENA_REGS_RESET_MISS_TX_CMPL ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  netif_notice (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int time_is_before_jiffies (unsigned long) ; 
 int /*<<< orphan*/  tx_err ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int check_missing_comp_in_tx_queue(struct ena_adapter *adapter,
					  struct ena_ring *tx_ring)
{
	struct ena_tx_buffer *tx_buf;
	unsigned long last_jiffies;
	u32 missed_tx = 0;
	int i, rc = 0;

	for (i = 0; i < tx_ring->ring_size; i++) {
		tx_buf = &tx_ring->tx_buffer_info[i];
		last_jiffies = tx_buf->last_jiffies;

		if (last_jiffies == 0)
			/* no pending Tx at this location */
			continue;

		if (unlikely(!tx_ring->first_interrupt && time_is_before_jiffies(last_jiffies +
			     2 * adapter->missing_tx_completion_to))) {
			/* If after graceful period interrupt is still not
			 * received, we schedule a reset
			 */
			netif_err(adapter, tx_err, adapter->netdev,
				  "Potential MSIX issue on Tx side Queue = %d. Reset the device\n",
				  tx_ring->qid);
			adapter->reset_reason = ENA_REGS_RESET_MISS_INTERRUPT;
			smp_mb__before_atomic();
			set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
			return -EIO;
		}

		if (unlikely(time_is_before_jiffies(last_jiffies +
				adapter->missing_tx_completion_to))) {
			if (!tx_buf->print_once)
				netif_notice(adapter, tx_err, adapter->netdev,
					     "Found a Tx that wasn't completed on time, qid %d, index %d.\n",
					     tx_ring->qid, i);

			tx_buf->print_once = 1;
			missed_tx++;
		}
	}

	if (unlikely(missed_tx > adapter->missing_tx_completion_threshold)) {
		netif_err(adapter, tx_err, adapter->netdev,
			  "The number of lost tx completions is above the threshold (%d > %d). Reset the device\n",
			  missed_tx,
			  adapter->missing_tx_completion_threshold);
		adapter->reset_reason =
			ENA_REGS_RESET_MISS_TX_CMPL;
		set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
		rc = -EIO;
	}

	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->tx_stats.missed_tx = missed_tx;
	u64_stats_update_end(&tx_ring->syncp);

	return rc;
}