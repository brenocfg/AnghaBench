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
struct myri10ge_slice_state {int /*<<< orphan*/  napi; int /*<<< orphan*/  dev; struct myri10ge_priv* mgp; int /*<<< orphan*/ * fw_stats; int /*<<< orphan*/  fw_stats_bus; TYPE_1__ rx_done; } ;
struct myri10ge_priv {int num_slices; int max_intr_slots; int /*<<< orphan*/  dev; struct myri10ge_slice_state* ss; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct myri10ge_slice_state* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myri10ge_free_slices (struct myri10ge_priv*) ; 
 int /*<<< orphan*/  myri10ge_napi_weight ; 
 int /*<<< orphan*/  myri10ge_poll ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int myri10ge_alloc_slices(struct myri10ge_priv *mgp)
{
	struct myri10ge_slice_state *ss;
	struct pci_dev *pdev = mgp->pdev;
	size_t bytes;
	int i;

	bytes = sizeof(*mgp->ss) * mgp->num_slices;
	mgp->ss = kzalloc(bytes, GFP_KERNEL);
	if (mgp->ss == NULL) {
		return -ENOMEM;
	}

	for (i = 0; i < mgp->num_slices; i++) {
		ss = &mgp->ss[i];
		bytes = mgp->max_intr_slots * sizeof(*ss->rx_done.entry);
		ss->rx_done.entry = dma_alloc_coherent(&pdev->dev, bytes,
						       &ss->rx_done.bus,
						       GFP_KERNEL);
		if (ss->rx_done.entry == NULL)
			goto abort;
		bytes = sizeof(*ss->fw_stats);
		ss->fw_stats = dma_alloc_coherent(&pdev->dev, bytes,
						  &ss->fw_stats_bus,
						  GFP_KERNEL);
		if (ss->fw_stats == NULL)
			goto abort;
		ss->mgp = mgp;
		ss->dev = mgp->dev;
		netif_napi_add(ss->dev, &ss->napi, myri10ge_poll,
			       myri10ge_napi_weight);
	}
	return 0;
abort:
	myri10ge_free_slices(mgp);
	return -ENOMEM;
}