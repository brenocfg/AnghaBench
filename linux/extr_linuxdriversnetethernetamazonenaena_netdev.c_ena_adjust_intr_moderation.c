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
struct ena_ring {scalar_t__ per_napi_bytes; scalar_t__ per_napi_packets; int /*<<< orphan*/  moder_tbl_idx; int /*<<< orphan*/  smoothed_interval; int /*<<< orphan*/  ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ena_com_calculate_interrupt_delay (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

inline void ena_adjust_intr_moderation(struct ena_ring *rx_ring,
				       struct ena_ring *tx_ring)
{
	/* We apply adaptive moderation on Rx path only.
	 * Tx uses static interrupt moderation.
	 */
	ena_com_calculate_interrupt_delay(rx_ring->ena_dev,
					  rx_ring->per_napi_packets,
					  rx_ring->per_napi_bytes,
					  &rx_ring->smoothed_interval,
					  &rx_ring->moder_tbl_idx);

	/* Reset per napi packets/bytes */
	tx_ring->per_napi_packets = 0;
	tx_ring->per_napi_bytes = 0;
	rx_ring->per_napi_packets = 0;
	rx_ring->per_napi_bytes = 0;
}