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
typedef  int /*<<< orphan*/  u32 ;
struct qed_hwfn {TYPE_2__* p_cxt_mngr; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
struct TYPE_4__ {TYPE_1__* conn_cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  cid_count; int /*<<< orphan*/  cids_per_vf; } ;

/* Variables and functions */

u32 qed_cxt_get_proto_cid_count(struct qed_hwfn *p_hwfn,
				enum protocol_type type, u32 *vf_cid)
{
	if (vf_cid)
		*vf_cid = p_hwfn->p_cxt_mngr->conn_cfg[type].cids_per_vf;

	return p_hwfn->p_cxt_mngr->conn_cfg[type].cid_count;
}