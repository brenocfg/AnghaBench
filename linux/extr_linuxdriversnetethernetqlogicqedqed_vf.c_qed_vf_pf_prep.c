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
typedef  union vfpf_tlvs {int dummy; } vfpf_tlvs ;
typedef  union pfvf_tlvs {int dummy; } pfvf_tlvs ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct vfpf_first_tlv {scalar_t__ reply_address; } ;
struct qed_vf_iov {scalar_t__ pf2vf_reply_phys; int /*<<< orphan*/ * offset; scalar_t__ pf2vf_reply; scalar_t__ vf2pf_request; int /*<<< orphan*/  mutex; } ;
struct qed_hwfn {struct qed_vf_iov* vf_iov_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 void* qed_add_tlv (struct qed_hwfn*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *qed_vf_pf_prep(struct qed_hwfn *p_hwfn, u16 type, u16 length)
{
	struct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	void *p_tlv;

	/* This lock is released when we receive PF's response
	 * in qed_send_msg2pf().
	 * So, qed_vf_pf_prep() and qed_send_msg2pf()
	 * must come in sequence.
	 */
	mutex_lock(&(p_iov->mutex));

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "preparing to send 0x%04x tlv over vf pf channel\n",
		   type);

	/* Reset Requst offset */
	p_iov->offset = (u8 *)p_iov->vf2pf_request;

	/* Clear mailbox - both request and reply */
	memset(p_iov->vf2pf_request, 0, sizeof(union vfpf_tlvs));
	memset(p_iov->pf2vf_reply, 0, sizeof(union pfvf_tlvs));

	/* Init type and length */
	p_tlv = qed_add_tlv(p_hwfn, &p_iov->offset, type, length);

	/* Init first tlv header */
	((struct vfpf_first_tlv *)p_tlv)->reply_address =
	    (u64)p_iov->pf2vf_reply_phys;

	return p_tlv;
}