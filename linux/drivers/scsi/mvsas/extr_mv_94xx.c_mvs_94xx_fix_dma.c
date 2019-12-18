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
struct mvs_prd_imt {int len; int /*<<< orphan*/  misc_ctl; } ;
struct mvs_prd {int /*<<< orphan*/  im_len; void* addr; } ;
struct mvs_info {int /*<<< orphan*/  bulk_buffer_dma1; int /*<<< orphan*/  bulk_buffer_dma; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {scalar_t__ revision; } ;

/* Variables and functions */
 int MAX_SG_ENTRY ; 
 int /*<<< orphan*/  PRD_CHAINED_ENTRY ; 
 scalar_t__ VANIR_A0_REV ; 
 scalar_t__ VANIR_B0_REV ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (struct mvs_prd*) ; 

__attribute__((used)) static void mvs_94xx_fix_dma(struct mvs_info *mvi, u32 phy_mask,
			     int buf_len, int from, void *prd)
{
	int i;
	struct mvs_prd *buf_prd = prd;
	dma_addr_t buf_dma;
	struct mvs_prd_imt im_len;

	*(u32 *)&im_len = 0;
	buf_prd += from;

#define PRD_CHAINED_ENTRY 0x01
	if ((mvi->pdev->revision == VANIR_A0_REV) ||
			(mvi->pdev->revision == VANIR_B0_REV))
		buf_dma = (phy_mask <= 0x08) ?
				mvi->bulk_buffer_dma : mvi->bulk_buffer_dma1;
	else
		return;

	for (i = from; i < MAX_SG_ENTRY; i++, ++buf_prd) {
		if (i == MAX_SG_ENTRY - 1) {
			buf_prd->addr = cpu_to_le64(virt_to_phys(buf_prd - 1));
			im_len.len = 2;
			im_len.misc_ctl = PRD_CHAINED_ENTRY;
		} else {
			buf_prd->addr = cpu_to_le64(buf_dma);
			im_len.len = buf_len;
		}
		buf_prd->im_len = cpu_to_le32(*(u32 *)&im_len);
	}
}