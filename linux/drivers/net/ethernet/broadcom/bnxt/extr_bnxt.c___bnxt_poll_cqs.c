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
struct bnxt_cp_ring_info {int /*<<< orphan*/  has_more_work; struct bnxt_cp_ring_info** cp_ring_arr; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 scalar_t__ __bnxt_poll_work (struct bnxt*,struct bnxt_cp_ring_info*,int) ; 

__attribute__((used)) static int __bnxt_poll_cqs(struct bnxt *bp, struct bnxt_napi *bnapi, int budget)
{
	struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	int i, work_done = 0;

	for (i = 0; i < 2; i++) {
		struct bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[i];

		if (cpr2) {
			work_done += __bnxt_poll_work(bp, cpr2,
						      budget - work_done);
			cpr->has_more_work |= cpr2->has_more_work;
		}
	}
	return work_done;
}