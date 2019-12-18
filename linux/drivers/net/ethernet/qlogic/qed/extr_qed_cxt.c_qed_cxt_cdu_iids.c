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
typedef  size_t u32 ;
struct qed_cxt_mngr {TYPE_1__* conn_cfg; } ;
struct qed_cdu_iids {int /*<<< orphan*/  per_vf_cids; int /*<<< orphan*/  pf_cids; } ;
struct TYPE_2__ {scalar_t__ cids_per_vf; scalar_t__ cid_count; } ;

/* Variables and functions */
 size_t MAX_CONN_TYPES ; 

__attribute__((used)) static void qed_cxt_cdu_iids(struct qed_cxt_mngr *p_mngr,
			     struct qed_cdu_iids *iids)
{
	u32 type;

	for (type = 0; type < MAX_CONN_TYPES; type++) {
		iids->pf_cids += p_mngr->conn_cfg[type].cid_count;
		iids->per_vf_cids += p_mngr->conn_cfg[type].cids_per_vf;
	}
}