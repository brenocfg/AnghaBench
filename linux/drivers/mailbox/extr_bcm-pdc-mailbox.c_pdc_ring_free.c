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
struct TYPE_3__ {int /*<<< orphan*/ * vbase; int /*<<< orphan*/  dmabase; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vbase; int /*<<< orphan*/  dmabase; } ;
struct pdc_state {TYPE_1__ rx_ring_alloc; int /*<<< orphan*/  ring_pool; TYPE_2__ tx_ring_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdc_ring_free(struct pdc_state *pdcs)
{
	if (pdcs->tx_ring_alloc.vbase) {
		dma_pool_free(pdcs->ring_pool, pdcs->tx_ring_alloc.vbase,
			      pdcs->tx_ring_alloc.dmabase);
		pdcs->tx_ring_alloc.vbase = NULL;
	}

	if (pdcs->rx_ring_alloc.vbase) {
		dma_pool_free(pdcs->ring_pool, pdcs->rx_ring_alloc.vbase,
			      pdcs->rx_ring_alloc.dmabase);
		pdcs->rx_ring_alloc.vbase = NULL;
	}
}