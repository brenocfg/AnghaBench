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
struct bnx2i_hba {int /*<<< orphan*/ * dummy_buffer; int /*<<< orphan*/  dummy_buf_dma; TYPE_1__* pcidev; int /*<<< orphan*/ * mp_bd_tbl; int /*<<< orphan*/  mp_bd_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2i_free_mp_bdt(struct bnx2i_hba *hba)
{
	if (hba->mp_bd_tbl) {
		dma_free_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  hba->mp_bd_tbl, hba->mp_bd_dma);
		hba->mp_bd_tbl = NULL;
	}
	if (hba->dummy_buffer) {
		dma_free_coherent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  hba->dummy_buffer, hba->dummy_buf_dma);
		hba->dummy_buffer = NULL;
	}
	return;
}