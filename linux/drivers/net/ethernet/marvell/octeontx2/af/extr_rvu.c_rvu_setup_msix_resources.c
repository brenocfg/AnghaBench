#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int max; } ;
struct rvu_pfvf {TYPE_1__ msix; void* msix_lfmap; } ;
struct rvu_hwinfo {int total_pfs; } ;
struct rvu {scalar_t__ msix_base_iova; int /*<<< orphan*/  dev; struct rvu_pfvf* hwvf; struct rvu_pfvf* pf; struct rvu_hwinfo* hw; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLKADDR_RVUM ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCI_MSIX_ENTRY_SIZE ; 
 int /*<<< orphan*/  RVU_AF_MSIXTR_BASE ; 
 int /*<<< orphan*/  RVU_PRIV_CONST ; 
 int /*<<< orphan*/  RVU_PRIV_HWVFX_INT_CFG (int) ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_CFG (int) ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_INT_CFG (int) ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_MSIX_CFG (int) ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_resource (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int rvu_alloc_bitmap (TYPE_1__*) ; 
 int rvu_alloc_rsrc_contig (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rvu_check_min_msix_vec (struct rvu*,int,int,int) ; 
 int /*<<< orphan*/  rvu_get_pf_numvfs (struct rvu*,int,int*,int*) ; 
 int rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rvu_setup_msix_resources(struct rvu *rvu)
{
	struct rvu_hwinfo *hw = rvu->hw;
	int pf, vf, numvfs, hwvf, err;
	int nvecs, offset, max_msix;
	struct rvu_pfvf *pfvf;
	u64 cfg, phy_addr;
	dma_addr_t iova;

	for (pf = 0; pf < hw->total_pfs; pf++) {
		cfg = rvu_read64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
		/* If PF is not enabled, nothing to do */
		if (!((cfg >> 20) & 0x01))
			continue;

		rvu_get_pf_numvfs(rvu, pf, &numvfs, &hwvf);

		pfvf = &rvu->pf[pf];
		/* Get num of MSIX vectors attached to this PF */
		cfg = rvu_read64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_MSIX_CFG(pf));
		pfvf->msix.max = ((cfg >> 32) & 0xFFF) + 1;
		rvu_check_min_msix_vec(rvu, pfvf->msix.max, pf, 0);

		/* Alloc msix bitmap for this PF */
		err = rvu_alloc_bitmap(&pfvf->msix);
		if (err)
			return err;

		/* Allocate memory for MSIX vector to RVU block LF mapping */
		pfvf->msix_lfmap = devm_kcalloc(rvu->dev, pfvf->msix.max,
						sizeof(u16), GFP_KERNEL);
		if (!pfvf->msix_lfmap)
			return -ENOMEM;

		/* For PF0 (AF) firmware will set msix vector offsets for
		 * AF, block AF and PF0_INT vectors, so jump to VFs.
		 */
		if (!pf)
			goto setup_vfmsix;

		/* Set MSIX offset for PF's 'RVU_PF_INT_VEC' vectors.
		 * These are allocated on driver init and never freed,
		 * so no need to set 'msix_lfmap' for these.
		 */
		cfg = rvu_read64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_INT_CFG(pf));
		nvecs = (cfg >> 12) & 0xFF;
		cfg &= ~0x7FFULL;
		offset = rvu_alloc_rsrc_contig(&pfvf->msix, nvecs);
		rvu_write64(rvu, BLKADDR_RVUM,
			    RVU_PRIV_PFX_INT_CFG(pf), cfg | offset);
setup_vfmsix:
		/* Alloc msix bitmap for VFs */
		for (vf = 0; vf < numvfs; vf++) {
			pfvf =  &rvu->hwvf[hwvf + vf];
			/* Get num of MSIX vectors attached to this VF */
			cfg = rvu_read64(rvu, BLKADDR_RVUM,
					 RVU_PRIV_PFX_MSIX_CFG(pf));
			pfvf->msix.max = (cfg & 0xFFF) + 1;
			rvu_check_min_msix_vec(rvu, pfvf->msix.max, pf, vf + 1);

			/* Alloc msix bitmap for this VF */
			err = rvu_alloc_bitmap(&pfvf->msix);
			if (err)
				return err;

			pfvf->msix_lfmap =
				devm_kcalloc(rvu->dev, pfvf->msix.max,
					     sizeof(u16), GFP_KERNEL);
			if (!pfvf->msix_lfmap)
				return -ENOMEM;

			/* Set MSIX offset for HWVF's 'RVU_VF_INT_VEC' vectors.
			 * These are allocated on driver init and never freed,
			 * so no need to set 'msix_lfmap' for these.
			 */
			cfg = rvu_read64(rvu, BLKADDR_RVUM,
					 RVU_PRIV_HWVFX_INT_CFG(hwvf + vf));
			nvecs = (cfg >> 12) & 0xFF;
			cfg &= ~0x7FFULL;
			offset = rvu_alloc_rsrc_contig(&pfvf->msix, nvecs);
			rvu_write64(rvu, BLKADDR_RVUM,
				    RVU_PRIV_HWVFX_INT_CFG(hwvf + vf),
				    cfg | offset);
		}
	}

	/* HW interprets RVU_AF_MSIXTR_BASE address as an IOVA, hence
	 * create a IOMMU mapping for the physcial address configured by
	 * firmware and reconfig RVU_AF_MSIXTR_BASE with IOVA.
	 */
	cfg = rvu_read64(rvu, BLKADDR_RVUM, RVU_PRIV_CONST);
	max_msix = cfg & 0xFFFFF;
	phy_addr = rvu_read64(rvu, BLKADDR_RVUM, RVU_AF_MSIXTR_BASE);
	iova = dma_map_resource(rvu->dev, phy_addr,
				max_msix * PCI_MSIX_ENTRY_SIZE,
				DMA_BIDIRECTIONAL, 0);

	if (dma_mapping_error(rvu->dev, iova))
		return -ENOMEM;

	rvu_write64(rvu, BLKADDR_RVUM, RVU_AF_MSIXTR_BASE, (u64)iova);
	rvu->msix_base_iova = iova;

	return 0;
}