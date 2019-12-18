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
struct tg3_napi {int /*<<< orphan*/ * rx_rcb; int /*<<< orphan*/  rx_rcb_mapping; int /*<<< orphan*/  prodring; } ;
struct tg3 {int irq_max; TYPE_1__* pdev; struct tg3_napi* napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG3_RX_RCB_RING_BYTES (struct tg3*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_rx_prodring_fini (struct tg3*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tg3_mem_rx_release(struct tg3 *tp)
{
	int i;

	for (i = 0; i < tp->irq_max; i++) {
		struct tg3_napi *tnapi = &tp->napi[i];

		tg3_rx_prodring_fini(tp, &tnapi->prodring);

		if (!tnapi->rx_rcb)
			continue;

		dma_free_coherent(&tp->pdev->dev,
				  TG3_RX_RCB_RING_BYTES(tp),
				  tnapi->rx_rcb,
				  tnapi->rx_rcb_mapping);
		tnapi->rx_rcb = NULL;
	}
}