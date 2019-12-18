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
struct rvu_hwinfo {int /*<<< orphan*/  total_pfs; } ;
struct rvu {struct rvu_hwinfo* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKADDR_RVUM ; 
 unsigned long long INTR_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RVU_AF_PFAF_MBOX_INT ; 
 int /*<<< orphan*/  RVU_AF_PFAF_MBOX_INT_ENA_W1S ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void rvu_enable_mbox_intr(struct rvu *rvu)
{
	struct rvu_hwinfo *hw = rvu->hw;

	/* Clear spurious irqs, if any */
	rvu_write64(rvu, BLKADDR_RVUM,
		    RVU_AF_PFAF_MBOX_INT, INTR_MASK(hw->total_pfs));

	/* Enable mailbox interrupt for all PFs except PF0 i.e AF itself */
	rvu_write64(rvu, BLKADDR_RVUM, RVU_AF_PFAF_MBOX_INT_ENA_W1S,
		    INTR_MASK(hw->total_pfs) & ~1ULL);
}