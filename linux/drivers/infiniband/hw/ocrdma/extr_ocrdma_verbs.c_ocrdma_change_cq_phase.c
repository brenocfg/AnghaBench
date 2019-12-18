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
typedef  scalar_t__ u16 ;
struct ocrdma_cqe {scalar_t__ flags_status_srcqpn; } ;
struct ocrdma_cq {int phase; scalar_t__ phase_change; } ;

/* Variables and functions */
 int OCRDMA_CQE_VALID ; 

__attribute__((used)) static void ocrdma_change_cq_phase(struct ocrdma_cq *cq, struct ocrdma_cqe *cqe,
				   u16 cur_getp)
{
	if (cq->phase_change) {
		if (cur_getp == 0)
			cq->phase = (~cq->phase & OCRDMA_CQE_VALID);
	} else {
		/* clear valid bit */
		cqe->flags_status_srcqpn = 0;
	}
}