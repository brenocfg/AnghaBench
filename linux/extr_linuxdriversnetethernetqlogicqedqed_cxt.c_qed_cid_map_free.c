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
typedef  size_t u32 ;
struct qed_hwfn {struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {TYPE_2__** acquired_vf; TYPE_1__* acquired; } ;
struct TYPE_4__ {scalar_t__ start_cid; scalar_t__ max_count; int /*<<< orphan*/  cid_map; } ;
struct TYPE_3__ {scalar_t__ start_cid; scalar_t__ max_count; int /*<<< orphan*/  cid_map; } ;

/* Variables and functions */
 size_t MAX_CONN_TYPES ; 
 size_t MAX_NUM_VFS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_cid_map_free(struct qed_hwfn *p_hwfn)
{
	struct qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 type, vf;

	for (type = 0; type < MAX_CONN_TYPES; type++) {
		kfree(p_mngr->acquired[type].cid_map);
		p_mngr->acquired[type].max_count = 0;
		p_mngr->acquired[type].start_cid = 0;

		for (vf = 0; vf < MAX_NUM_VFS; vf++) {
			kfree(p_mngr->acquired_vf[type][vf].cid_map);
			p_mngr->acquired_vf[type][vf].max_count = 0;
			p_mngr->acquired_vf[type][vf].start_cid = 0;
		}
	}
}