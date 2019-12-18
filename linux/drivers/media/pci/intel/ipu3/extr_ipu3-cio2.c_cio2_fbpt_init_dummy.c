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
struct cio2_device {int dummy_page_bus_addr; int* dummy_lop; int dummy_lop_bus_addr; void* dummy_page; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CIO2_PAGE_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  cio2_fbpt_exit_dummy (struct cio2_device*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cio2_fbpt_init_dummy(struct cio2_device *cio2)
{
	unsigned int i;

	cio2->dummy_page = dma_alloc_coherent(&cio2->pci_dev->dev,
					      CIO2_PAGE_SIZE,
					      &cio2->dummy_page_bus_addr,
					      GFP_KERNEL);
	cio2->dummy_lop = dma_alloc_coherent(&cio2->pci_dev->dev,
					     CIO2_PAGE_SIZE,
					     &cio2->dummy_lop_bus_addr,
					     GFP_KERNEL);
	if (!cio2->dummy_page || !cio2->dummy_lop) {
		cio2_fbpt_exit_dummy(cio2);
		return -ENOMEM;
	}
	/*
	 * List of Pointers(LOP) contains 1024x32b pointers to 4KB page each
	 * Initialize each entry to dummy_page bus base address.
	 */
	for (i = 0; i < CIO2_PAGE_SIZE / sizeof(*cio2->dummy_lop); i++)
		cio2->dummy_lop[i] = cio2->dummy_page_bus_addr >> PAGE_SHIFT;

	return 0;
}