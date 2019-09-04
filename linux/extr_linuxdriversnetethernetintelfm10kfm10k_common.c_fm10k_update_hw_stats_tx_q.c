#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  count; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;
struct fm10k_hw_stats_q {int tx_stats_idx; TYPE_1__ tx_bytes; TYPE_2__ tx_packets; } ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_QBTC_L (int) ; 
 int /*<<< orphan*/  FM10K_QPTC (int) ; 
 int FM10K_STAT_VALID ; 
 int /*<<< orphan*/  FM10K_TXQCTL (int) ; 
 int FM10K_TXQCTL_ID_MASK ; 
 int fm10k_read_hw_stats_32b (struct fm10k_hw*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ fm10k_read_hw_stats_48b (struct fm10k_hw*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_update_hw_base_32b (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fm10k_update_hw_base_48b (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void fm10k_update_hw_stats_tx_q(struct fm10k_hw *hw,
				       struct fm10k_hw_stats_q *q,
				       u32 idx)
{
	u32 id_tx, id_tx_prev, tx_packets;
	u64 tx_bytes = 0;

	/* Retrieve TX Owner Data */
	id_tx = fm10k_read_reg(hw, FM10K_TXQCTL(idx));

	/* Process TX Ring */
	do {
		tx_packets = fm10k_read_hw_stats_32b(hw, FM10K_QPTC(idx),
						     &q->tx_packets);

		if (tx_packets)
			tx_bytes = fm10k_read_hw_stats_48b(hw,
							   FM10K_QBTC_L(idx),
							   &q->tx_bytes);

		/* Re-Check Owner Data */
		id_tx_prev = id_tx;
		id_tx = fm10k_read_reg(hw, FM10K_TXQCTL(idx));
	} while ((id_tx ^ id_tx_prev) & FM10K_TXQCTL_ID_MASK);

	/* drop non-ID bits and set VALID ID bit */
	id_tx &= FM10K_TXQCTL_ID_MASK;
	id_tx |= FM10K_STAT_VALID;

	/* update packet counts */
	if (q->tx_stats_idx == id_tx) {
		q->tx_packets.count += tx_packets;
		q->tx_bytes.count += tx_bytes;
	}

	/* update bases and record ID */
	fm10k_update_hw_base_32b(&q->tx_packets, tx_packets);
	fm10k_update_hw_base_48b(&q->tx_bytes, tx_bytes);

	q->tx_stats_idx = id_tx;
}