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
typedef  size_t u16 ;
struct bnxt_tx_ring_info {size_t tx_cons; struct bnxt_sw_tx_bd* tx_buf_ring; } ;
struct bnxt_sw_tx_bd {size_t rx_prod; } ;
struct bnxt_rx_ring_info {size_t rx_prod; int /*<<< orphan*/  rx_doorbell; } ;
struct bnxt_napi {struct bnxt_rx_ring_info* rx_ring; struct bnxt_tx_ring_info* tx_ring; } ;
struct bnxt {scalar_t__ tx_ring_size; } ;

/* Variables and functions */
 size_t DB_KEY_RX ; 
 size_t NEXT_TX (size_t) ; 
 int /*<<< orphan*/  bnxt_db_write (struct bnxt*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ bnxt_tx_avail (struct bnxt*,struct bnxt_tx_ring_info*) ; 

void bnxt_tx_int_xdp(struct bnxt *bp, struct bnxt_napi *bnapi, int nr_pkts)
{
	struct bnxt_tx_ring_info *txr = bnapi->tx_ring;
	struct bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	struct bnxt_sw_tx_bd *tx_buf;
	u16 tx_cons = txr->tx_cons;
	u16 last_tx_cons = tx_cons;
	u16 rx_prod;
	int i;

	for (i = 0; i < nr_pkts; i++) {
		last_tx_cons = tx_cons;
		tx_cons = NEXT_TX(tx_cons);
	}
	txr->tx_cons = tx_cons;
	if (bnxt_tx_avail(bp, txr) == bp->tx_ring_size) {
		rx_prod = rxr->rx_prod;
	} else {
		tx_buf = &txr->tx_buf_ring[last_tx_cons];
		rx_prod = tx_buf->rx_prod;
	}
	bnxt_db_write(bp, rxr->rx_doorbell, DB_KEY_RX | rx_prod);
}