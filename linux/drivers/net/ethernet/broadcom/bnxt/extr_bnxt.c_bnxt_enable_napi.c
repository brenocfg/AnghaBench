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
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  work; } ;
struct bnxt_cp_ring_info {TYPE_1__ dim; } ;
struct bnxt {int cp_nr_rings; TYPE_2__** bnapi; } ;
struct TYPE_4__ {int in_reset; int /*<<< orphan*/  napi; scalar_t__ rx_ring; struct bnxt_cp_ring_info cp_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_dim_work ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_enable_napi(struct bnxt *bp)
{
	int i;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_cp_ring_info *cpr = &bp->bnapi[i]->cp_ring;
		bp->bnapi[i]->in_reset = false;

		if (bp->bnapi[i]->rx_ring) {
			INIT_WORK(&cpr->dim.work, bnxt_dim_work);
			cpr->dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
		}
		napi_enable(&bp->bnapi[i]->napi);
	}
}