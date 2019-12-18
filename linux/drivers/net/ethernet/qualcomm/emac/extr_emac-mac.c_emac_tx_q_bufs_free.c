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
struct TYPE_2__ {scalar_t__ size; scalar_t__ dma_addr; int /*<<< orphan*/ * v_addr; int /*<<< orphan*/ * tpbuff; } ;
struct emac_tx_queue {TYPE_1__ tpd; } ;
struct emac_adapter {struct emac_tx_queue tx_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_tx_q_descs_free (struct emac_adapter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emac_tx_q_bufs_free(struct emac_adapter *adpt)
{
	struct emac_tx_queue *tx_q = &adpt->tx_q;

	emac_tx_q_descs_free(adpt);

	kfree(tx_q->tpd.tpbuff);
	tx_q->tpd.tpbuff = NULL;
	tx_q->tpd.v_addr = NULL;
	tx_q->tpd.dma_addr = 0;
	tx_q->tpd.size = 0;
}