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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt_vnic_info {int flags; int mc_list_size; scalar_t__ rss_table_dma_addr; scalar_t__ rss_hash_key_dma_addr; void* rss_table; void* rss_hash_key; int /*<<< orphan*/  fw_grp_ids; void* mc_list; scalar_t__ mc_list_mapping; int /*<<< orphan*/  uc_list; } ;
struct bnxt {int nr_vnics; int flags; int rx_nr_rings; struct bnxt_vnic_info* vnic_info; struct pci_dev* pdev; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_NEW_RSS_CAP ; 
 int BNXT_MAX_MC_ADDRS ; 
 int BNXT_MAX_UC_ADDRS ; 
 int BNXT_VNIC_MCAST_FLAG ; 
 int BNXT_VNIC_RSS_FLAG ; 
 int BNXT_VNIC_UCAST_FLAG ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HW_HASH_INDEX_SIZE ; 
 int L1_CACHE_ALIGN (int) ; 
 int PAGE_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_alloc_vnic_attributes(struct bnxt *bp)
{
	int i, rc = 0, size;
	struct bnxt_vnic_info *vnic;
	struct pci_dev *pdev = bp->pdev;
	int max_rings;

	for (i = 0; i < bp->nr_vnics; i++) {
		vnic = &bp->vnic_info[i];

		if (vnic->flags & BNXT_VNIC_UCAST_FLAG) {
			int mem_size = (BNXT_MAX_UC_ADDRS - 1) * ETH_ALEN;

			if (mem_size > 0) {
				vnic->uc_list = kmalloc(mem_size, GFP_KERNEL);
				if (!vnic->uc_list) {
					rc = -ENOMEM;
					goto out;
				}
			}
		}

		if (vnic->flags & BNXT_VNIC_MCAST_FLAG) {
			vnic->mc_list_size = BNXT_MAX_MC_ADDRS * ETH_ALEN;
			vnic->mc_list =
				dma_alloc_coherent(&pdev->dev,
						   vnic->mc_list_size,
						   &vnic->mc_list_mapping,
						   GFP_KERNEL);
			if (!vnic->mc_list) {
				rc = -ENOMEM;
				goto out;
			}
		}

		if (bp->flags & BNXT_FLAG_CHIP_P5)
			goto vnic_skip_grps;

		if (vnic->flags & BNXT_VNIC_RSS_FLAG)
			max_rings = bp->rx_nr_rings;
		else
			max_rings = 1;

		vnic->fw_grp_ids = kcalloc(max_rings, sizeof(u16), GFP_KERNEL);
		if (!vnic->fw_grp_ids) {
			rc = -ENOMEM;
			goto out;
		}
vnic_skip_grps:
		if ((bp->flags & BNXT_FLAG_NEW_RSS_CAP) &&
		    !(vnic->flags & BNXT_VNIC_RSS_FLAG))
			continue;

		/* Allocate rss table and hash key */
		vnic->rss_table = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
						     &vnic->rss_table_dma_addr,
						     GFP_KERNEL);
		if (!vnic->rss_table) {
			rc = -ENOMEM;
			goto out;
		}

		size = L1_CACHE_ALIGN(HW_HASH_INDEX_SIZE * sizeof(u16));

		vnic->rss_hash_key = ((void *)vnic->rss_table) + size;
		vnic->rss_hash_key_dma_addr = vnic->rss_table_dma_addr + size;
	}
	return 0;

out:
	return rc;
}