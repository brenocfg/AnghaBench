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
struct mvneta_tx_queue {int descs_phys; int size; int /*<<< orphan*/  done_pkts_coal; int /*<<< orphan*/  id; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVETH_TXQ_TOKEN_CFG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVETH_TXQ_TOKEN_COUNT_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVNETA_TXQ_BASE_ADDR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVNETA_TXQ_SIZE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_tx_done_pkts_coal_set (struct mvneta_port*,struct mvneta_tx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvneta_txq_hw_init(struct mvneta_port *pp,
			       struct mvneta_tx_queue *txq)
{
	/* Set maximum bandwidth for enabled TXQs */
	mvreg_write(pp, MVETH_TXQ_TOKEN_CFG_REG(txq->id), 0x03ffffff);
	mvreg_write(pp, MVETH_TXQ_TOKEN_COUNT_REG(txq->id), 0x3fffffff);

	/* Set Tx descriptors queue starting address */
	mvreg_write(pp, MVNETA_TXQ_BASE_ADDR_REG(txq->id), txq->descs_phys);
	mvreg_write(pp, MVNETA_TXQ_SIZE_REG(txq->id), txq->size);

	mvneta_tx_done_pkts_coal_set(pp, txq, txq->done_pkts_coal);
}