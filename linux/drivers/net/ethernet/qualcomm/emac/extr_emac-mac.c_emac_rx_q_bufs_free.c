#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; scalar_t__ dma_addr; int /*<<< orphan*/ * v_addr; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ dma_addr; int /*<<< orphan*/ * v_addr; int /*<<< orphan*/ * rfbuff; } ;
struct emac_rx_queue {TYPE_1__ rrd; TYPE_2__ rfd; } ;
struct emac_adapter {struct emac_rx_queue rx_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_rx_q_free_descs (struct emac_adapter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emac_rx_q_bufs_free(struct emac_adapter *adpt)
{
	struct emac_rx_queue *rx_q = &adpt->rx_q;

	emac_rx_q_free_descs(adpt);

	kfree(rx_q->rfd.rfbuff);
	rx_q->rfd.rfbuff   = NULL;

	rx_q->rfd.v_addr   = NULL;
	rx_q->rfd.dma_addr = 0;
	rx_q->rfd.size     = 0;

	rx_q->rrd.v_addr   = NULL;
	rx_q->rrd.dma_addr = 0;
	rx_q->rrd.size     = 0;
}