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
struct bnxt_ring_struct {scalar_t__ fw_ring_id; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/  cp_raw_cons; int /*<<< orphan*/  cp_db; struct bnxt_ring_struct cp_ring_struct; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int cp_nr_rings; struct bnxt_napi** bnapi; } ;

/* Variables and functions */
 scalar_t__ INVALID_HW_RING_ID ; 
 int /*<<< orphan*/  bnxt_db_nq (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_disable_int(struct bnxt *bp)
{
	int i;

	if (!bp->bnapi)
		return;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		struct bnxt_ring_struct *ring = &cpr->cp_ring_struct;

		if (ring->fw_ring_id != INVALID_HW_RING_ID)
			bnxt_db_nq(bp, &cpr->cp_db, cpr->cp_raw_cons);
	}
}