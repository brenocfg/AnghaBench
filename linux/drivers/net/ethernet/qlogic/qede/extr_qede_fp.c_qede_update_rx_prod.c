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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct qede_rx_queue {int /*<<< orphan*/  hw_rxq_prod_addr; int /*<<< orphan*/  rx_comp_ring; int /*<<< orphan*/  rx_bd_ring; } ;
struct qede_dev {int dummy; } ;
struct eth_rx_prod_data {void* cqe_prod; void* bd_prod; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  rx_prods ;

/* Variables and functions */
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_ram_wr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_chain_get_prod_idx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

void qede_update_rx_prod(struct qede_dev *edev, struct qede_rx_queue *rxq)
{
	u16 bd_prod = qed_chain_get_prod_idx(&rxq->rx_bd_ring);
	u16 cqe_prod = qed_chain_get_prod_idx(&rxq->rx_comp_ring);
	struct eth_rx_prod_data rx_prods = {0};

	/* Update producers */
	rx_prods.bd_prod = cpu_to_le16(bd_prod);
	rx_prods.cqe_prod = cpu_to_le16(cqe_prod);

	/* Make sure that the BD and SGE data is updated before updating the
	 * producers since FW might read the BD/SGE right after the producer
	 * is updated.
	 */
	wmb();

	internal_ram_wr(rxq->hw_rxq_prod_addr, sizeof(rx_prods),
			(u32 *)&rx_prods);
}