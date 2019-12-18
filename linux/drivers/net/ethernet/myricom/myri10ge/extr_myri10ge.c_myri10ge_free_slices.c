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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * entry; int /*<<< orphan*/  bus; } ;
struct myri10ge_slice_state {int /*<<< orphan*/  napi; int /*<<< orphan*/ * fw_stats; int /*<<< orphan*/  fw_stats_bus; TYPE_1__ rx_done; } ;
struct myri10ge_priv {int num_slices; int max_intr_slots; struct myri10ge_slice_state* ss; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct myri10ge_slice_state*) ; 
 int /*<<< orphan*/  napi_hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void myri10ge_free_slices(struct myri10ge_priv *mgp)
{
	struct myri10ge_slice_state *ss;
	struct pci_dev *pdev = mgp->pdev;
	size_t bytes;
	int i;

	if (mgp->ss == NULL)
		return;

	for (i = 0; i < mgp->num_slices; i++) {
		ss = &mgp->ss[i];
		if (ss->rx_done.entry != NULL) {
			bytes = mgp->max_intr_slots *
			    sizeof(*ss->rx_done.entry);
			dma_free_coherent(&pdev->dev, bytes,
					  ss->rx_done.entry, ss->rx_done.bus);
			ss->rx_done.entry = NULL;
		}
		if (ss->fw_stats != NULL) {
			bytes = sizeof(*ss->fw_stats);
			dma_free_coherent(&pdev->dev, bytes,
					  ss->fw_stats, ss->fw_stats_bus);
			ss->fw_stats = NULL;
		}
		napi_hash_del(&ss->napi);
		netif_napi_del(&ss->napi);
	}
	/* Wait till napi structs are no longer used, and then free ss. */
	synchronize_rcu();
	kfree(mgp->ss);
	mgp->ss = NULL;
}