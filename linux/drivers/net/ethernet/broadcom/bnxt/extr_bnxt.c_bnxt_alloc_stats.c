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
typedef  size_t u32 ;
struct tx_port_stats_ext {int dummy; } ;
struct tx_port_stats {int dummy; } ;
struct rx_port_stats_ext {int dummy; } ;
struct rx_port_stats {int dummy; } ;
struct pcie_ctx_hw_stats {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/  hw_stats_ctx_id; void* hw_stats; int /*<<< orphan*/  hw_stats_map; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {size_t hw_ring_stats_size; size_t cp_nr_rings; scalar_t__ chip_num; int hw_port_stats_size; int hwrm_spec_code; int fw_cap; int /*<<< orphan*/  flags; void* hw_pcie_stats; int /*<<< orphan*/  hw_pcie_stats_map; int /*<<< orphan*/  hw_tx_port_stats_ext_map; void* hw_tx_port_stats_ext; void* hw_rx_port_stats_ext; int /*<<< orphan*/  hw_rx_port_stats_ext_map; int /*<<< orphan*/  hw_rx_port_stats_map; scalar_t__ hw_tx_port_stats_map; void* hw_rx_port_stats; void* hw_tx_port_stats; struct bnxt_napi** bnapi; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FLAG_PCIE_STATS ; 
 int /*<<< orphan*/  BNXT_FLAG_PORT_STATS ; 
 int /*<<< orphan*/  BNXT_FLAG_PORT_STATS_EXT ; 
 int BNXT_FW_CAP_EXT_STATS_SUPPORTED ; 
 int BNXT_FW_CAP_PCIE_STATS_SUPPORTED ; 
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 scalar_t__ CHIP_NUM_58700 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INVALID_STATS_CTX_ID ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_alloc_stats(struct bnxt *bp)
{
	u32 size, i;
	struct pci_dev *pdev = bp->pdev;

	size = bp->hw_ring_stats_size;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;

		cpr->hw_stats = dma_alloc_coherent(&pdev->dev, size,
						   &cpr->hw_stats_map,
						   GFP_KERNEL);
		if (!cpr->hw_stats)
			return -ENOMEM;

		cpr->hw_stats_ctx_id = INVALID_STATS_CTX_ID;
	}

	if (BNXT_VF(bp) || bp->chip_num == CHIP_NUM_58700)
		return 0;

	if (bp->hw_rx_port_stats)
		goto alloc_ext_stats;

	bp->hw_port_stats_size = sizeof(struct rx_port_stats) +
				 sizeof(struct tx_port_stats) + 1024;

	bp->hw_rx_port_stats =
		dma_alloc_coherent(&pdev->dev, bp->hw_port_stats_size,
				   &bp->hw_rx_port_stats_map,
				   GFP_KERNEL);
	if (!bp->hw_rx_port_stats)
		return -ENOMEM;

	bp->hw_tx_port_stats = (void *)(bp->hw_rx_port_stats + 1) + 512;
	bp->hw_tx_port_stats_map = bp->hw_rx_port_stats_map +
				   sizeof(struct rx_port_stats) + 512;
	bp->flags |= BNXT_FLAG_PORT_STATS;

alloc_ext_stats:
	/* Display extended statistics only if FW supports it */
	if (bp->hwrm_spec_code < 0x10804 || bp->hwrm_spec_code == 0x10900)
		if (!(bp->fw_cap & BNXT_FW_CAP_EXT_STATS_SUPPORTED))
			return 0;

	if (bp->hw_rx_port_stats_ext)
		goto alloc_tx_ext_stats;

	bp->hw_rx_port_stats_ext =
		dma_alloc_coherent(&pdev->dev, sizeof(struct rx_port_stats_ext),
				   &bp->hw_rx_port_stats_ext_map, GFP_KERNEL);
	if (!bp->hw_rx_port_stats_ext)
		return 0;

alloc_tx_ext_stats:
	if (bp->hw_tx_port_stats_ext)
		goto alloc_pcie_stats;

	if (bp->hwrm_spec_code >= 0x10902 ||
	    (bp->fw_cap & BNXT_FW_CAP_EXT_STATS_SUPPORTED)) {
		bp->hw_tx_port_stats_ext =
			dma_alloc_coherent(&pdev->dev,
					   sizeof(struct tx_port_stats_ext),
					   &bp->hw_tx_port_stats_ext_map,
					   GFP_KERNEL);
	}
	bp->flags |= BNXT_FLAG_PORT_STATS_EXT;

alloc_pcie_stats:
	if (bp->hw_pcie_stats ||
	    !(bp->fw_cap & BNXT_FW_CAP_PCIE_STATS_SUPPORTED))
		return 0;

	bp->hw_pcie_stats =
		dma_alloc_coherent(&pdev->dev, sizeof(struct pcie_ctx_hw_stats),
				   &bp->hw_pcie_stats_map, GFP_KERNEL);
	if (!bp->hw_pcie_stats)
		return 0;

	bp->flags |= BNXT_FLAG_PCIE_STATS;
	return 0;
}