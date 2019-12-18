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
typedef  int u64 ;
struct bnxt_db_info {int db_key64; int /*<<< orphan*/  doorbell; } ;
struct bnxt_cp_ring_info {scalar_t__ had_work_done; int /*<<< orphan*/  cp_raw_cons; struct bnxt_db_info cp_db; struct bnxt_cp_ring_info** cp_ring_arr; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int RING_CMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bnxt_poll_work_done (struct bnxt*,struct bnxt_napi*) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __bnxt_poll_cqs_done(struct bnxt *bp, struct bnxt_napi *bnapi,
				 u64 dbr_type, bool all)
{
	struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	int i;

	for (i = 0; i < 2; i++) {
		struct bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[i];
		struct bnxt_db_info *db;

		if (cpr2 && (all || cpr2->had_work_done)) {
			db = &cpr2->cp_db;
			writeq(db->db_key64 | dbr_type |
			       RING_CMP(cpr2->cp_raw_cons), db->doorbell);
			cpr2->had_work_done = 0;
		}
	}
	__bnxt_poll_work_done(bp, bnapi);
}