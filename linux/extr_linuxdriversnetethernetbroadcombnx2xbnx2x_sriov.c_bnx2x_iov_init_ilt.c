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
typedef  int u16 ;
struct hw_dma {int /*<<< orphan*/  size; int /*<<< orphan*/  mapping; int /*<<< orphan*/  addr; } ;
struct bnx2x_ilt {TYPE_1__* lines; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  page_mapping; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int BNX2X_VF_CIDS ; 
 struct bnx2x_ilt* BP_ILT (struct bnx2x*) ; 
 struct hw_dma* BP_VF_CXT_PAGE (struct bnx2x*,int) ; 
 int ILT_PAGE_CIDS ; 
 int /*<<< orphan*/  IS_SRIOV (struct bnx2x*) ; 

int bnx2x_iov_init_ilt(struct bnx2x *bp, u16 line)
{
	int i;
	struct bnx2x_ilt *ilt = BP_ILT(bp);

	if (!IS_SRIOV(bp))
		return line;

	/* set vfs ilt lines */
	for (i = 0; i < BNX2X_VF_CIDS/ILT_PAGE_CIDS; i++) {
		struct hw_dma *hw_cxt = BP_VF_CXT_PAGE(bp, i);

		ilt->lines[line+i].page = hw_cxt->addr;
		ilt->lines[line+i].page_mapping = hw_cxt->mapping;
		ilt->lines[line+i].size = hw_cxt->size; /* doesn't matter */
	}
	return line + i;
}