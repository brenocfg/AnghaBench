#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void u8 ;
typedef  size_t u32 ;
struct qed_dev {TYPE_1__* pdev; } ;
struct TYPE_6__ {void** pp_virt_addr_tbl; } ;
struct TYPE_5__ {void* p_virt_table; int /*<<< orphan*/  p_phys_table; } ;
struct qed_chain {size_t page_cnt; TYPE_3__ pbl; TYPE_2__ pbl_sp; int /*<<< orphan*/  b_external_pbl; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t QED_CHAIN_PAGE_SIZE ; 
 size_t QED_CHAIN_PBL_ENTRY_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (void**) ; 

__attribute__((used)) static void qed_chain_free_pbl(struct qed_dev *cdev, struct qed_chain *p_chain)
{
	void **pp_virt_addr_tbl = p_chain->pbl.pp_virt_addr_tbl;
	u32 page_cnt = p_chain->page_cnt, i, pbl_size;
	u8 *p_pbl_virt = p_chain->pbl_sp.p_virt_table;

	if (!pp_virt_addr_tbl)
		return;

	if (!p_pbl_virt)
		goto out;

	for (i = 0; i < page_cnt; i++) {
		if (!pp_virt_addr_tbl[i])
			break;

		dma_free_coherent(&cdev->pdev->dev,
				  QED_CHAIN_PAGE_SIZE,
				  pp_virt_addr_tbl[i],
				  *(dma_addr_t *)p_pbl_virt);

		p_pbl_virt += QED_CHAIN_PBL_ENTRY_SIZE;
	}

	pbl_size = page_cnt * QED_CHAIN_PBL_ENTRY_SIZE;

	if (!p_chain->b_external_pbl)
		dma_free_coherent(&cdev->pdev->dev,
				  pbl_size,
				  p_chain->pbl_sp.p_virt_table,
				  p_chain->pbl_sp.p_phys_table);
out:
	vfree(p_chain->pbl.pp_virt_addr_tbl);
	p_chain->pbl.pp_virt_addr_tbl = NULL;
}