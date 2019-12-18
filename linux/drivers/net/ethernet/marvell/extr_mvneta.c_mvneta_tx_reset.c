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
struct mvneta_port {int /*<<< orphan*/ * txqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_PORT_TX_DMA_RESET ; 
 int /*<<< orphan*/  MVNETA_PORT_TX_RESET ; 
 int /*<<< orphan*/  mvneta_txq_done_force (struct mvneta_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txq_number ; 

__attribute__((used)) static void mvneta_tx_reset(struct mvneta_port *pp)
{
	int queue;

	/* free the skb's in the tx ring */
	for (queue = 0; queue < txq_number; queue++)
		mvneta_txq_done_force(pp, &pp->txqs[queue]);

	mvreg_write(pp, MVNETA_PORT_TX_RESET, MVNETA_PORT_TX_DMA_RESET);
	mvreg_write(pp, MVNETA_PORT_TX_RESET, 0);
}