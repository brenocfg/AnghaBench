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
struct kvmppc_spapr_tce_table {int /*<<< orphan*/  page_shift; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_NONE ; 
 long H_PARAMETER ; 
 long H_SUCCESS ; 
 unsigned long TCE_PCI_READ ; 
 unsigned long TCE_PCI_WRITE ; 
 scalar_t__ iommu_tce_check_gpa (int /*<<< orphan*/ ,unsigned long) ; 
 int iommu_tce_direction (unsigned long) ; 

long kvmppc_tce_validate(struct kvmppc_spapr_tce_table *stt, unsigned long tce)
{
	unsigned long gpa = tce & ~(TCE_PCI_READ | TCE_PCI_WRITE);
	enum dma_data_direction dir = iommu_tce_direction(tce);

	/* Allow userspace to poison TCE table */
	if (dir == DMA_NONE)
		return H_SUCCESS;

	if (iommu_tce_check_gpa(stt->page_shift, gpa))
		return H_PARAMETER;

	return H_SUCCESS;
}