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
struct tg3_napi {int /*<<< orphan*/ * tx_buffers; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  tx_desc_mapping; } ;
struct tg3 {int irq_max; TYPE_1__* pdev; struct tg3_napi* napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG3_TX_RING_BYTES ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tg3_mem_tx_release(struct tg3 *tp)
{
	int i;

	for (i = 0; i < tp->irq_max; i++) {
		struct tg3_napi *tnapi = &tp->napi[i];

		if (tnapi->tx_ring) {
			dma_free_coherent(&tp->pdev->dev, TG3_TX_RING_BYTES,
				tnapi->tx_ring, tnapi->tx_desc_mapping);
			tnapi->tx_ring = NULL;
		}

		kfree(tnapi->tx_buffers);
		tnapi->tx_buffers = NULL;
	}
}