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
typedef  unsigned long long u8 ;
typedef  unsigned long long u64 ;
struct rvu {TYPE_1__* hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned long long total_pfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (unsigned long long) ; 
 int /*<<< orphan*/  BLKADDR_RVUM ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RVU_AF_PFME_INT ; 
 int /*<<< orphan*/  RVU_AF_PFTRPEND ; 
 unsigned long long rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rvu_me_pf_intr_handler(int irq, void *rvu_irq)
{
	struct rvu *rvu = (struct rvu *)rvu_irq;
	u64 intr;
	u8  pf;

	intr = rvu_read64(rvu, BLKADDR_RVUM, RVU_AF_PFME_INT);

	/* Nothing to be done here other than clearing the
	 * TRPEND bit.
	 */
	for (pf = 0; pf < rvu->hw->total_pfs; pf++) {
		if (intr & (1ULL << pf)) {
			/* clear the trpend due to ME(master enable) */
			rvu_write64(rvu, BLKADDR_RVUM, RVU_AF_PFTRPEND,
				    BIT_ULL(pf));
			/* clear interrupt */
			rvu_write64(rvu, BLKADDR_RVUM, RVU_AF_PFME_INT,
				    BIT_ULL(pf));
		}
	}

	return IRQ_HANDLED;
}