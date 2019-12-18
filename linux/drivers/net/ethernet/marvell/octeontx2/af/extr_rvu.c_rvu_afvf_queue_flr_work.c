#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct rvu {TYPE_2__* flr_wrk; int /*<<< orphan*/  flr_wq; TYPE_1__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct TYPE_3__ {int total_pfs; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  RVU_PF_VFFLR_INTX (int) ; 
 int /*<<< orphan*/  RVU_PF_VFFLR_INT_ENA_W1CX (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rvupf_read64 (struct rvu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvupf_write64 (struct rvu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rvu_afvf_queue_flr_work(struct rvu *rvu, int start_vf, int numvfs)
{
	int dev, vf, reg = 0;
	u64 intr;

	if (start_vf >= 64)
		reg = 1;

	intr = rvupf_read64(rvu, RVU_PF_VFFLR_INTX(reg));
	if (!intr)
		return;

	for (vf = 0; vf < numvfs; vf++) {
		if (!(intr & BIT_ULL(vf)))
			continue;
		dev = vf + start_vf + rvu->hw->total_pfs;
		queue_work(rvu->flr_wq, &rvu->flr_wrk[dev].work);
		/* Clear and disable the interrupt */
		rvupf_write64(rvu, RVU_PF_VFFLR_INTX(reg), BIT_ULL(vf));
		rvupf_write64(rvu, RVU_PF_VFFLR_INT_ENA_W1CX(reg), BIT_ULL(vf));
	}
}