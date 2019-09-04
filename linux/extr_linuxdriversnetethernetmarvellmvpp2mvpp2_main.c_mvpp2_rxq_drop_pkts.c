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
typedef  int u32 ;
struct mvpp2_rx_queue {int /*<<< orphan*/  id; } ;
struct mvpp2_rx_desc {int dummy; } ;
struct mvpp2_port {int dummy; } ;

/* Variables and functions */
 int MVPP2_RXD_BM_POOL_ID_MASK ; 
 int MVPP2_RXD_BM_POOL_ID_OFFS ; 
 int /*<<< orphan*/  mvpp2_bm_pool_put (struct mvpp2_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_rxdesc_cookie_get (struct mvpp2_port*,struct mvpp2_rx_desc*) ; 
 int /*<<< orphan*/  mvpp2_rxdesc_dma_addr_get (struct mvpp2_port*,struct mvpp2_rx_desc*) ; 
 int mvpp2_rxdesc_status_get (struct mvpp2_port*,struct mvpp2_rx_desc*) ; 
 struct mvpp2_rx_desc* mvpp2_rxq_next_desc_get (struct mvpp2_rx_queue*) ; 
 int mvpp2_rxq_received (struct mvpp2_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_rxq_status_update (struct mvpp2_port*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mvpp2_rxq_drop_pkts(struct mvpp2_port *port,
				struct mvpp2_rx_queue *rxq)
{
	int rx_received, i;

	rx_received = mvpp2_rxq_received(port, rxq->id);
	if (!rx_received)
		return;

	for (i = 0; i < rx_received; i++) {
		struct mvpp2_rx_desc *rx_desc = mvpp2_rxq_next_desc_get(rxq);
		u32 status = mvpp2_rxdesc_status_get(port, rx_desc);
		int pool;

		pool = (status & MVPP2_RXD_BM_POOL_ID_MASK) >>
			MVPP2_RXD_BM_POOL_ID_OFFS;

		mvpp2_bm_pool_put(port, pool,
				  mvpp2_rxdesc_dma_addr_get(port, rx_desc),
				  mvpp2_rxdesc_cookie_get(port, rx_desc));
	}
	mvpp2_rxq_status_update(port, rxq->id, rx_received, rx_received);
}