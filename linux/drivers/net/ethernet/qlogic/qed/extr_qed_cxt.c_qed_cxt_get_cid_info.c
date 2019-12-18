#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct qed_hwfn {struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {TYPE_3__* ilt_shadow; TYPE_2__* clients; } ;
struct qed_cxt_info {size_t iid; int type; scalar_t__ p_cxt; } ;
struct qed_cid_acquired_map {int dummy; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
struct TYPE_6__ {scalar_t__ p_virt; } ;
struct TYPE_4__ {size_t val; } ;
struct TYPE_5__ {TYPE_1__ p_size; } ;

/* Variables and functions */
 size_t CONN_CXT_SIZE (struct qed_hwfn*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int,char*,size_t,scalar_t__,size_t) ; 
 int EINVAL ; 
 size_t ILT_CLI_CDUC ; 
 size_t ILT_PAGE_IN_BYTES (size_t) ; 
 int /*<<< orphan*/  QED_CXT_PF_CID ; 
 int QED_MSG_CXT ; 
 int QED_MSG_ILT ; 
 int qed_cxt_test_cid_acquired (struct qed_hwfn*,size_t,int /*<<< orphan*/ ,int*,struct qed_cid_acquired_map**) ; 

int qed_cxt_get_cid_info(struct qed_hwfn *p_hwfn, struct qed_cxt_info *p_info)
{
	struct qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct qed_cid_acquired_map *p_map = NULL;
	u32 conn_cxt_size, hw_p_size, cxts_per_p, line;
	enum protocol_type type;
	bool b_acquired;

	/* Test acquired and find matching per-protocol map */
	b_acquired = qed_cxt_test_cid_acquired(p_hwfn, p_info->iid,
					       QED_CXT_PF_CID, &type, &p_map);

	if (!b_acquired)
		return -EINVAL;

	/* set the protocl type */
	p_info->type = type;

	/* compute context virtual pointer */
	hw_p_size = p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC].p_size.val;

	conn_cxt_size = CONN_CXT_SIZE(p_hwfn);
	cxts_per_p = ILT_PAGE_IN_BYTES(hw_p_size) / conn_cxt_size;
	line = p_info->iid / cxts_per_p;

	/* Make sure context is allocated (dynamic allocation) */
	if (!p_mngr->ilt_shadow[line].p_virt)
		return -EINVAL;

	p_info->p_cxt = p_mngr->ilt_shadow[line].p_virt +
			p_info->iid % cxts_per_p * conn_cxt_size;

	DP_VERBOSE(p_hwfn, (QED_MSG_ILT | QED_MSG_CXT),
		   "Accessing ILT shadow[%d]: CXT pointer is at %p (for iid %d)\n",
		   p_info->iid / cxts_per_p, p_info->p_cxt, p_info->iid);

	return 0;
}