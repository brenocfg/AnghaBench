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
struct TYPE_2__ {scalar_t__ SG_handle; int /*<<< orphan*/  SGarray; } ;
struct ivtv {TYPE_1__ udma; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  ivtv_udma_sync_for_cpu (struct ivtv*) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ivtv_udma_alloc(struct ivtv *itv)
{
	if (itv->udma.SG_handle == 0) {
		/* Map DMA Page Array Buffer */
		itv->udma.SG_handle = pci_map_single(itv->pdev, itv->udma.SGarray,
			   sizeof(itv->udma.SGarray), PCI_DMA_TODEVICE);
		ivtv_udma_sync_for_cpu(itv);
	}
}