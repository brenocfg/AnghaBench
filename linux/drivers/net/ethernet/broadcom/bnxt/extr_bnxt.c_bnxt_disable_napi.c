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
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct bnxt_cp_ring_info {TYPE_1__ dim; } ;
struct bnxt {int cp_nr_rings; TYPE_2__** bnapi; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; scalar_t__ rx_ring; struct bnxt_cp_ring_info cp_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_disable_napi(struct bnxt *bp)
{
	int i;

	if (!bp->bnapi)
		return;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_cp_ring_info *cpr = &bp->bnapi[i]->cp_ring;

		if (bp->bnapi[i]->rx_ring)
			cancel_work_sync(&cpr->dim.work);

		napi_disable(&bp->bnapi[i]->napi);
	}
}