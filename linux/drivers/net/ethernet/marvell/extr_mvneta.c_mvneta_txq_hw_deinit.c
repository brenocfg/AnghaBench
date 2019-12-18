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
struct mvneta_tx_queue {int /*<<< orphan*/  id; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVETH_TXQ_TOKEN_CFG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVETH_TXQ_TOKEN_COUNT_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVNETA_TXQ_BASE_ADDR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVNETA_TXQ_SIZE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_txq_hw_deinit(struct mvneta_port *pp,
				 struct mvneta_tx_queue *txq)
{
	/* Set minimum bandwidth for disabled TXQs */
	mvreg_write(pp, MVETH_TXQ_TOKEN_CFG_REG(txq->id), 0);
	mvreg_write(pp, MVETH_TXQ_TOKEN_COUNT_REG(txq->id), 0);

	/* Set Tx descriptors queue starting address and size */
	mvreg_write(pp, MVNETA_TXQ_BASE_ADDR_REG(txq->id), 0);
	mvreg_write(pp, MVNETA_TXQ_SIZE_REG(txq->id), 0);
}