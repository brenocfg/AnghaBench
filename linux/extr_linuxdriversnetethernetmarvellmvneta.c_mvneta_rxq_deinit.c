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
struct mvneta_rx_queue {int size; scalar_t__ left_size; int /*<<< orphan*/ * skb; scalar_t__ refill_num; scalar_t__ first_to_refill; scalar_t__ descs_phys; scalar_t__ next_desc_to_proc; scalar_t__ last_desc; int /*<<< orphan*/ * descs; } ;
struct mvneta_port {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int MVNETA_DESC_ALIGNED_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mvneta_rxq_drop_pkts (struct mvneta_port*,struct mvneta_rx_queue*) ; 

__attribute__((used)) static void mvneta_rxq_deinit(struct mvneta_port *pp,
			      struct mvneta_rx_queue *rxq)
{
	mvneta_rxq_drop_pkts(pp, rxq);

	if (rxq->skb)
		dev_kfree_skb_any(rxq->skb);

	if (rxq->descs)
		dma_free_coherent(pp->dev->dev.parent,
				  rxq->size * MVNETA_DESC_ALIGNED_SIZE,
				  rxq->descs,
				  rxq->descs_phys);

	rxq->descs             = NULL;
	rxq->last_desc         = 0;
	rxq->next_desc_to_proc = 0;
	rxq->descs_phys        = 0;
	rxq->first_to_refill   = 0;
	rxq->refill_num        = 0;
	rxq->skb               = NULL;
	rxq->left_size         = 0;
}