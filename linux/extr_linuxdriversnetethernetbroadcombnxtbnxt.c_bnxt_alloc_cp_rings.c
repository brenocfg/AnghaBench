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
struct bnxt_ring_struct {int map_idx; } ;
struct bnxt_cp_ring_info {struct bnxt_ring_struct cp_ring_struct; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int cp_nr_rings; struct bnxt_napi** bnapi; } ;

/* Variables and functions */
 int bnxt_alloc_ring (struct bnxt*,struct bnxt_ring_struct*) ; 
 int bnxt_get_ulp_msix_base (struct bnxt*) ; 
 int bnxt_get_ulp_msix_num (struct bnxt*) ; 

__attribute__((used)) static int bnxt_alloc_cp_rings(struct bnxt *bp)
{
	int i, rc, ulp_base_vec, ulp_msix;

	ulp_msix = bnxt_get_ulp_msix_num(bp);
	ulp_base_vec = bnxt_get_ulp_msix_base(bp);
	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr;
		struct bnxt_ring_struct *ring;

		if (!bnapi)
			continue;

		cpr = &bnapi->cp_ring;
		ring = &cpr->cp_ring_struct;

		rc = bnxt_alloc_ring(bp, ring);
		if (rc)
			return rc;

		if (ulp_msix && i >= ulp_base_vec)
			ring->map_idx = i + ulp_msix;
		else
			ring->map_idx = i;
	}
	return 0;
}