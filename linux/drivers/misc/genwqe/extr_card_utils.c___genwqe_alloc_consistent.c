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
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_ORDER ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_order (size_t) ; 

void *__genwqe_alloc_consistent(struct genwqe_dev *cd, size_t size,
			       dma_addr_t *dma_handle)
{
	if (get_order(size) >= MAX_ORDER)
		return NULL;

	return dma_alloc_coherent(&cd->pci_dev->dev, size, dma_handle,
				  GFP_KERNEL);
}