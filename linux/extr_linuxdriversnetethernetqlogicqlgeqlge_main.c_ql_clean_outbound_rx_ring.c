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
typedef  scalar_t__ u32 ;
struct tx_ring {int wq_len; int /*<<< orphan*/  wq_id; int /*<<< orphan*/  tx_count; } ;
struct rx_ring {scalar_t__ cnsmr_idx; int /*<<< orphan*/  prod_idx_sh_reg; scalar_t__ curr_entry; int /*<<< orphan*/  cq_id; struct ql_adapter* qdev; } ;
struct ql_adapter {int /*<<< orphan*/  ndev; struct tx_ring* tx_ring; } ;
struct ob_mac_iocb_rsp {int opcode; size_t txq_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
#define  OPCODE_OB_MAC_IOCB 129 
#define  OPCODE_OB_MAC_TSO_IOCB 128 
 scalar_t__ __netif_subqueue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_process_mac_tx_intr (struct ql_adapter*,struct ob_mac_iocb_rsp*) ; 
 scalar_t__ ql_read_sh_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_update_cq (struct rx_ring*) ; 
 int /*<<< orphan*/  ql_write_cq_idx (struct rx_ring*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  rx_status ; 

__attribute__((used)) static int ql_clean_outbound_rx_ring(struct rx_ring *rx_ring)
{
	struct ql_adapter *qdev = rx_ring->qdev;
	u32 prod = ql_read_sh_reg(rx_ring->prod_idx_sh_reg);
	struct ob_mac_iocb_rsp *net_rsp = NULL;
	int count = 0;

	struct tx_ring *tx_ring;
	/* While there are entries in the completion queue. */
	while (prod != rx_ring->cnsmr_idx) {

		netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "cq_id = %d, prod = %d, cnsmr = %d\n",
			     rx_ring->cq_id, prod, rx_ring->cnsmr_idx);

		net_rsp = (struct ob_mac_iocb_rsp *)rx_ring->curr_entry;
		rmb();
		switch (net_rsp->opcode) {

		case OPCODE_OB_MAC_TSO_IOCB:
		case OPCODE_OB_MAC_IOCB:
			ql_process_mac_tx_intr(qdev, net_rsp);
			break;
		default:
			netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "Hit default case, not handled! dropping the packet, opcode = %x.\n",
				     net_rsp->opcode);
		}
		count++;
		ql_update_cq(rx_ring);
		prod = ql_read_sh_reg(rx_ring->prod_idx_sh_reg);
	}
	if (!net_rsp)
		return 0;
	ql_write_cq_idx(rx_ring);
	tx_ring = &qdev->tx_ring[net_rsp->txq_idx];
	if (__netif_subqueue_stopped(qdev->ndev, tx_ring->wq_id)) {
		if ((atomic_read(&tx_ring->tx_count) > (tx_ring->wq_len / 4)))
			/*
			 * The queue got stopped because the tx_ring was full.
			 * Wake it up, because it's now at least 25% empty.
			 */
			netif_wake_subqueue(qdev->ndev, tx_ring->wq_id);
	}

	return count;
}