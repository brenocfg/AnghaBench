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
typedef  int u64 ;
struct sysinfo {int /*<<< orphan*/  totalram; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct MPT3SAS_ADAPTER {scalar_t__ hba_mpi_version_belonged; int dma_mask; int sge_size; int /*<<< orphan*/ * base_add_sg_single; scalar_t__ is_mcpu_endpoint; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  Mpi2SGESimple64_t ;
typedef  int /*<<< orphan*/  Mpi2SGESimple32_t ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 scalar_t__ MPI2_VERSION ; 
 int /*<<< orphan*/  _base_add_sg_single_32 ; 
 int /*<<< orphan*/  _base_add_sg_single_64 ; 
 int /*<<< orphan*/  convert_to_kb (int /*<<< orphan*/ ) ; 
 int dma_get_required_mask (int /*<<< orphan*/ *) ; 
 scalar_t__ dma_set_coherent_mask (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dma_set_mask (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dma_set_mask_and_coherent (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 

__attribute__((used)) static int
_base_config_dma_addressing(struct MPT3SAS_ADAPTER *ioc, struct pci_dev *pdev)
{
	u64 required_mask, coherent_mask;
	struct sysinfo s;
	/* Set 63 bit DMA mask for all SAS3 and SAS35 controllers */
	int dma_mask = (ioc->hba_mpi_version_belonged > MPI2_VERSION) ? 63 : 64;

	if (ioc->is_mcpu_endpoint)
		goto try_32bit;

	required_mask = dma_get_required_mask(&pdev->dev);
	if (sizeof(dma_addr_t) == 4 || required_mask == 32)
		goto try_32bit;

	if (ioc->dma_mask)
		coherent_mask = DMA_BIT_MASK(dma_mask);
	else
		coherent_mask = DMA_BIT_MASK(32);

	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(dma_mask)) ||
	    dma_set_coherent_mask(&pdev->dev, coherent_mask))
		goto try_32bit;

	ioc->base_add_sg_single = &_base_add_sg_single_64;
	ioc->sge_size = sizeof(Mpi2SGESimple64_t);
	ioc->dma_mask = dma_mask;
	goto out;

 try_32bit:
	if (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)))
		return -ENODEV;

	ioc->base_add_sg_single = &_base_add_sg_single_32;
	ioc->sge_size = sizeof(Mpi2SGESimple32_t);
	ioc->dma_mask = 32;
 out:
	si_meminfo(&s);
	ioc_info(ioc, "%d BIT PCI BUS DMA ADDRESSING SUPPORTED, total mem (%ld kB)\n",
		 ioc->dma_mask, convert_to_kb(s.totalram));

	return 0;
}