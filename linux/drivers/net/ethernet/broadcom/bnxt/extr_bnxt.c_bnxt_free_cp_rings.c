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
struct bnxt_ring_struct {int /*<<< orphan*/  ring_mem; } ;
struct bnxt_cp_ring_info {struct bnxt_cp_ring_info** cp_ring_arr; struct bnxt_ring_struct cp_ring_struct; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int cp_nr_rings; struct bnxt_napi** bnapi; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_free_ring (struct bnxt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bnxt_cp_ring_info*) ; 

__attribute__((used)) static void bnxt_free_cp_rings(struct bnxt *bp)
{
	int i;

	if (!bp->bnapi)
		return;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr;
		struct bnxt_ring_struct *ring;
		int j;

		if (!bnapi)
			continue;

		cpr = &bnapi->cp_ring;
		ring = &cpr->cp_ring_struct;

		bnxt_free_ring(bp, &ring->ring_mem);

		for (j = 0; j < 2; j++) {
			struct bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[j];

			if (cpr2) {
				ring = &cpr2->cp_ring_struct;
				bnxt_free_ring(bp, &ring->ring_mem);
				kfree(cpr2);
				cpr->cp_ring_arr[j] = NULL;
			}
		}
	}
}