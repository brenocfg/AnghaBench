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
struct genwqe_dev {TYPE_1__* pci_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,void*,int /*<<< orphan*/ ) ; 

void __genwqe_free_consistent(struct genwqe_dev *cd, size_t size,
			     void *vaddr, dma_addr_t dma_handle)
{
	if (vaddr == NULL)
		return;

	dma_free_coherent(&cd->pci_dev->dev, size, vaddr, dma_handle);
}