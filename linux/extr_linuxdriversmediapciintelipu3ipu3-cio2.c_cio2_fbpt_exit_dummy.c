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
struct cio2_device {int /*<<< orphan*/ * dummy_page; int /*<<< orphan*/  dummy_page_bus_addr; TYPE_1__* pci_dev; int /*<<< orphan*/ * dummy_lop; int /*<<< orphan*/  dummy_lop_bus_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO2_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cio2_fbpt_exit_dummy(struct cio2_device *cio2)
{
	if (cio2->dummy_lop) {
		dma_free_coherent(&cio2->pci_dev->dev, CIO2_PAGE_SIZE,
				  cio2->dummy_lop, cio2->dummy_lop_bus_addr);
		cio2->dummy_lop = NULL;
	}
	if (cio2->dummy_page) {
		dma_free_coherent(&cio2->pci_dev->dev, CIO2_PAGE_SIZE,
				  cio2->dummy_page, cio2->dummy_page_bus_addr);
		cio2->dummy_page = NULL;
	}
}