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
struct rx_ring {scalar_t__ cnsmr_idx; int /*<<< orphan*/  prod_idx_sh_reg; struct ql_net_rsp_iocb* curr_entry; int /*<<< orphan*/  cq_id; struct ql_adapter* qdev; } ;
struct ql_net_rsp_iocb {int opcode; } ;
struct ql_adapter {int /*<<< orphan*/  ndev; } ;
struct ib_mac_iocb_rsp {int dummy; } ;
struct ib_ae_iocb_rsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
#define  OPCODE_IB_AE_IOCB 129 
#define  OPCODE_IB_MAC_IOCB 128 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ql_process_chip_ae_intr (struct ql_adapter*,struct ib_ae_iocb_rsp*) ; 
 int /*<<< orphan*/  ql_process_mac_rx_intr (struct ql_adapter*,struct rx_ring*,struct ib_mac_iocb_rsp*) ; 
 scalar_t__ ql_read_sh_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_update_buffer_queues (struct ql_adapter*,struct rx_ring*) ; 
 int /*<<< orphan*/  ql_update_cq (struct rx_ring*) ; 
 int /*<<< orphan*/  ql_write_cq_idx (struct rx_ring*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  rx_status ; 

__attribute__((used)) static int ql_clean_inbound_rx_ring(struct rx_ring *rx_ring, int budget)
{
	struct ql_adapter *qdev = rx_ring->qdev;
	u32 prod = ql_read_sh_reg(rx_ring->prod_idx_sh_reg);
	struct ql_net_rsp_iocb *net_rsp;
	int count = 0;

	/* While there are entries in the completion queue. */
	while (prod != rx_ring->cnsmr_idx) {

		netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "cq_id = %d, prod = %d, cnsmr = %d\n",
			     rx_ring->cq_id, prod, rx_ring->cnsmr_idx);

		net_rsp = rx_ring->curr_entry;
		rmb();
		switch (net_rsp->opcode) {
		case OPCODE_IB_MAC_IOCB:
			ql_process_mac_rx_intr(qdev, rx_ring,
					       (struct ib_mac_iocb_rsp *)
					       net_rsp);
			break;

		case OPCODE_IB_AE_IOCB:
			ql_process_chip_ae_intr(qdev, (struct ib_ae_iocb_rsp *)
						net_rsp);
			break;
		default:
			netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "Hit default case, not handled! dropping the packet, opcode = %x.\n",
				     net_rsp->opcode);
			break;
		}
		count++;
		ql_update_cq(rx_ring);
		prod = ql_read_sh_reg(rx_ring->prod_idx_sh_reg);
		if (count == budget)
			break;
	}
	ql_update_buffer_queues(qdev, rx_ring);
	ql_write_cq_idx(rx_ring);
	return count;
}