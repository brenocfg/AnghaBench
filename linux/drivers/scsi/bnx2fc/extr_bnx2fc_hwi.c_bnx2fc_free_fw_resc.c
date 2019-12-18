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
typedef  int u32 ;
struct regpair {int dummy; } ;
struct fcoe_t2_hash_table_entry {int dummy; } ;
struct bnx2fc_hba {int /*<<< orphan*/ * t2_hash_tbl; int /*<<< orphan*/  t2_hash_tbl_dma; TYPE_1__* pcidev; int /*<<< orphan*/ * t2_hash_tbl_ptr; int /*<<< orphan*/  t2_hash_tbl_ptr_dma; int /*<<< orphan*/ * dummy_buffer; int /*<<< orphan*/  dummy_buf_dma; int /*<<< orphan*/ * stats_buffer; int /*<<< orphan*/  stats_buf_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2FC_NUM_MAX_SESS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bnx2fc_free_hash_table (struct bnx2fc_hba*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bnx2fc_free_fw_resc(struct bnx2fc_hba *hba)
{
	u32 mem_size;

	if (hba->stats_buffer) {
		dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
				  hba->stats_buffer, hba->stats_buf_dma);
		hba->stats_buffer = NULL;
	}

	if (hba->dummy_buffer) {
		dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
				  hba->dummy_buffer, hba->dummy_buf_dma);
		hba->dummy_buffer = NULL;
	}

	if (hba->t2_hash_tbl_ptr) {
		mem_size = BNX2FC_NUM_MAX_SESS * sizeof(struct regpair);
		dma_free_coherent(&hba->pcidev->dev, mem_size,
				    hba->t2_hash_tbl_ptr,
				    hba->t2_hash_tbl_ptr_dma);
		hba->t2_hash_tbl_ptr = NULL;
	}

	if (hba->t2_hash_tbl) {
		mem_size = BNX2FC_NUM_MAX_SESS *
			    sizeof(struct fcoe_t2_hash_table_entry);
		dma_free_coherent(&hba->pcidev->dev, mem_size,
				    hba->t2_hash_tbl, hba->t2_hash_tbl_dma);
		hba->t2_hash_tbl = NULL;
	}
	bnx2fc_free_hash_table(hba);
}