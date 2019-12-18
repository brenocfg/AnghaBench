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
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
union pfvf_tlvs {TYPE_2__ default_resp; } ;
struct qed_hwfn {TYPE_3__* vf_iov_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; union pfvf_tlvs* pf2vf_reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qed_vf_pf_req_end(struct qed_hwfn *p_hwfn, int req_status)
{
	union pfvf_tlvs *resp = p_hwfn->vf_iov_info->pf2vf_reply;

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "VF request status = 0x%x, PF reply status = 0x%x\n",
		   req_status, resp->default_resp.hdr.status);

	mutex_unlock(&(p_hwfn->vf_iov_info->mutex));
}