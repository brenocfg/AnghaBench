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
struct rvu {int num_vec; int /*<<< orphan*/  pdev; scalar_t__* irq_allocated; TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_pfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKADDR_RVUM ; 
 unsigned long long INTR_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RVU_AF_PFAF_MBOX_INT_ENA_W1C ; 
 int /*<<< orphan*/  RVU_AF_PFFLR_INT_ENA_W1C ; 
 int /*<<< orphan*/  RVU_AF_PFME_INT_ENA_W1C ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rvu*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void rvu_unregister_interrupts(struct rvu *rvu)
{
	int irq;

	/* Disable the Mbox interrupt */
	rvu_write64(rvu, BLKADDR_RVUM, RVU_AF_PFAF_MBOX_INT_ENA_W1C,
		    INTR_MASK(rvu->hw->total_pfs) & ~1ULL);

	/* Disable the PF FLR interrupt */
	rvu_write64(rvu, BLKADDR_RVUM, RVU_AF_PFFLR_INT_ENA_W1C,
		    INTR_MASK(rvu->hw->total_pfs) & ~1ULL);

	/* Disable the PF ME interrupt */
	rvu_write64(rvu, BLKADDR_RVUM, RVU_AF_PFME_INT_ENA_W1C,
		    INTR_MASK(rvu->hw->total_pfs) & ~1ULL);

	for (irq = 0; irq < rvu->num_vec; irq++) {
		if (rvu->irq_allocated[irq])
			free_irq(pci_irq_vector(rvu->pdev, irq), rvu);
	}

	pci_free_irq_vectors(rvu->pdev);
	rvu->num_vec = 0;
}