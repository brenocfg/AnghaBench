#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct flexcop_dma {int size; int /*<<< orphan*/  dma_addr0; int /*<<< orphan*/  cpu_addr0; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct flexcop_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void flexcop_dma_free(struct flexcop_dma *dma)
{
	pci_free_consistent(dma->pdev, dma->size*2,
			dma->cpu_addr0, dma->dma_addr0);
	memset(dma, 0, sizeof(struct flexcop_dma));
}