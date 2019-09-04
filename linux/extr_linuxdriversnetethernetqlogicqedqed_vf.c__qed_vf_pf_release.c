#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union vfpf_tlvs {int dummy; } vfpf_tlvs ;
typedef  union pfvf_tlvs {int dummy; } pfvf_tlvs ;
typedef  int u32 ;
struct vfpf_first_tlv {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  phys; TYPE_5__* p_virt; } ;
struct qed_vf_iov {TYPE_4__ bulletin; int /*<<< orphan*/  pf2vf_reply_phys; TYPE_5__* pf2vf_reply; int /*<<< orphan*/  vf2pf_request_phys; TYPE_5__* vf2pf_request; int /*<<< orphan*/  offset; } ;
struct qed_hwfn {struct qed_vf_iov* vf_iov_info; TYPE_3__* cdev; scalar_t__ b_int_enabled; } ;
struct qed_bulletin_content {int dummy; } ;
struct TYPE_6__ {scalar_t__ status; } ;
struct pfvf_def_resp_tlv {TYPE_1__ hdr; } ;
struct channel_list_end_tlv {int dummy; } ;
struct TYPE_10__ {struct pfvf_def_resp_tlv default_resp; } ;
struct TYPE_8__ {TYPE_2__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  CHANNEL_TLV_RELEASE ; 
 int EAGAIN ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_vf_iov*) ; 
 int /*<<< orphan*/  qed_add_tlv (struct qed_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qed_send_msg2pf (struct qed_hwfn*,scalar_t__*,int) ; 
 struct vfpf_first_tlv* qed_vf_pf_prep (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_vf_pf_req_end (struct qed_hwfn*,int) ; 

__attribute__((used)) static int _qed_vf_pf_release(struct qed_hwfn *p_hwfn, bool b_final)
{
	struct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	struct pfvf_def_resp_tlv *resp;
	struct vfpf_first_tlv *req;
	u32 size;
	int rc;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_RELEASE, sizeof(*req));

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, sizeof(struct channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->default_resp;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, sizeof(*resp));

	if (!rc && resp->hdr.status != PFVF_STATUS_SUCCESS)
		rc = -EAGAIN;

	qed_vf_pf_req_end(p_hwfn, rc);
	if (!b_final)
		return rc;

	p_hwfn->b_int_enabled = 0;

	if (p_iov->vf2pf_request)
		dma_free_coherent(&p_hwfn->cdev->pdev->dev,
				  sizeof(union vfpf_tlvs),
				  p_iov->vf2pf_request,
				  p_iov->vf2pf_request_phys);
	if (p_iov->pf2vf_reply)
		dma_free_coherent(&p_hwfn->cdev->pdev->dev,
				  sizeof(union pfvf_tlvs),
				  p_iov->pf2vf_reply, p_iov->pf2vf_reply_phys);

	if (p_iov->bulletin.p_virt) {
		size = sizeof(struct qed_bulletin_content);
		dma_free_coherent(&p_hwfn->cdev->pdev->dev,
				  size,
				  p_iov->bulletin.p_virt, p_iov->bulletin.phys);
	}

	kfree(p_hwfn->vf_iov_info);
	p_hwfn->vf_iov_info = NULL;

	return rc;
}