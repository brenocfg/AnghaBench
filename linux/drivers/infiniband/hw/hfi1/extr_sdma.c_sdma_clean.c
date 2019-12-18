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
typedef  int /*<<< orphan*/  u64 ;
struct sdma_engine {void* descq; int descq_cnt; int /*<<< orphan*/ * tx_ring; scalar_t__ descq_phys; scalar_t__ head_phys; int /*<<< orphan*/ * head_dma; } ;
struct hfi1_devdata {int sdma_heads_size; struct sdma_engine* sdma_rht; struct sdma_engine* per_sdma; int /*<<< orphan*/  sde_map_lock; int /*<<< orphan*/  sdma_map; TYPE_1__* pcidev; scalar_t__ sdma_heads_phys; int /*<<< orphan*/ * sdma_heads_dma; scalar_t__ sdma_pad_phys; int /*<<< orphan*/ * sdma_pad_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SDMA_PAD ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct sdma_engine*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_free_and_destroy (struct sdma_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_map_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_rht_free ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void sdma_clean(struct hfi1_devdata *dd, size_t num_engines)
{
	size_t i;
	struct sdma_engine *sde;

	if (dd->sdma_pad_dma) {
		dma_free_coherent(&dd->pcidev->dev, SDMA_PAD,
				  (void *)dd->sdma_pad_dma,
				  dd->sdma_pad_phys);
		dd->sdma_pad_dma = NULL;
		dd->sdma_pad_phys = 0;
	}
	if (dd->sdma_heads_dma) {
		dma_free_coherent(&dd->pcidev->dev, dd->sdma_heads_size,
				  (void *)dd->sdma_heads_dma,
				  dd->sdma_heads_phys);
		dd->sdma_heads_dma = NULL;
		dd->sdma_heads_phys = 0;
	}
	for (i = 0; dd->per_sdma && i < num_engines; ++i) {
		sde = &dd->per_sdma[i];

		sde->head_dma = NULL;
		sde->head_phys = 0;

		if (sde->descq) {
			dma_free_coherent(
				&dd->pcidev->dev,
				sde->descq_cnt * sizeof(u64[2]),
				sde->descq,
				sde->descq_phys
			);
			sde->descq = NULL;
			sde->descq_phys = 0;
		}
		kvfree(sde->tx_ring);
		sde->tx_ring = NULL;
	}
	spin_lock_irq(&dd->sde_map_lock);
	sdma_map_free(rcu_access_pointer(dd->sdma_map));
	RCU_INIT_POINTER(dd->sdma_map, NULL);
	spin_unlock_irq(&dd->sde_map_lock);
	synchronize_rcu();
	kfree(dd->per_sdma);
	dd->per_sdma = NULL;

	if (dd->sdma_rht) {
		rhashtable_free_and_destroy(dd->sdma_rht, sdma_rht_free, NULL);
		kfree(dd->sdma_rht);
		dd->sdma_rht = NULL;
	}
}