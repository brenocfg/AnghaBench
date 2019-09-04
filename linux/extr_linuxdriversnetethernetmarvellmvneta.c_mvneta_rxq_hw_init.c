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
struct mvneta_rx_queue {int /*<<< orphan*/  size; int /*<<< orphan*/  time_coal; int /*<<< orphan*/  pkts_coal; int /*<<< orphan*/  id; int /*<<< orphan*/  descs_phys; } ;
struct mvneta_port {scalar_t__ rx_offset_correction; int /*<<< orphan*/  pkt_size; int /*<<< orphan*/  bm_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_RXQ_BASE_ADDR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVNETA_RXQ_SIZE_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ MVNETA_RX_BUF_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ NET_SKB_PAD ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ SZ_64K ; 
 int /*<<< orphan*/  mvneta_rx_pkts_coal_set (struct mvneta_port*,struct mvneta_rx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_rx_time_coal_set (struct mvneta_port*,struct mvneta_rx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_rxq_bm_disable (struct mvneta_port*,struct mvneta_rx_queue*) ; 
 int /*<<< orphan*/  mvneta_rxq_bm_enable (struct mvneta_port*,struct mvneta_rx_queue*) ; 
 int /*<<< orphan*/  mvneta_rxq_buf_size_set (struct mvneta_port*,struct mvneta_rx_queue*,scalar_t__) ; 
 int /*<<< orphan*/  mvneta_rxq_fill (struct mvneta_port*,struct mvneta_rx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_rxq_long_pool_set (struct mvneta_port*,struct mvneta_rx_queue*) ; 
 int /*<<< orphan*/  mvneta_rxq_non_occup_desc_add (struct mvneta_port*,struct mvneta_rx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_rxq_offset_set (struct mvneta_port*,struct mvneta_rx_queue*,scalar_t__) ; 
 int /*<<< orphan*/  mvneta_rxq_short_pool_set (struct mvneta_port*,struct mvneta_rx_queue*) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_rxq_hw_init(struct mvneta_port *pp,
			       struct mvneta_rx_queue *rxq)
{
	/* Set Rx descriptors queue starting address */
	mvreg_write(pp, MVNETA_RXQ_BASE_ADDR_REG(rxq->id), rxq->descs_phys);
	mvreg_write(pp, MVNETA_RXQ_SIZE_REG(rxq->id), rxq->size);

	/* Set coalescing pkts and time */
	mvneta_rx_pkts_coal_set(pp, rxq, rxq->pkts_coal);
	mvneta_rx_time_coal_set(pp, rxq, rxq->time_coal);

	if (!pp->bm_priv) {
		/* Set Offset */
		mvneta_rxq_offset_set(pp, rxq, 0);
		mvneta_rxq_buf_size_set(pp, rxq, PAGE_SIZE < SZ_64K ?
					PAGE_SIZE :
					MVNETA_RX_BUF_SIZE(pp->pkt_size));
		mvneta_rxq_bm_disable(pp, rxq);
		mvneta_rxq_fill(pp, rxq, rxq->size);
	} else {
		/* Set Offset */
		mvneta_rxq_offset_set(pp, rxq,
				      NET_SKB_PAD - pp->rx_offset_correction);

		mvneta_rxq_bm_enable(pp, rxq);
		/* Fill RXQ with buffers from RX pool */
		mvneta_rxq_long_pool_set(pp, rxq);
		mvneta_rxq_short_pool_set(pp, rxq);
		mvneta_rxq_non_occup_desc_add(pp, rxq, rxq->size);
	}
}