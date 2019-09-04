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
typedef  union pfvf_tlvs {int dummy; } pfvf_tlvs ;
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qed_iov_vf_mbx {TYPE_4__* req_virt; scalar_t__ reply_phys; TYPE_5__* reply_virt; } ;
struct qed_vf_info {void* abs_vf_id; struct qed_iov_vf_mbx vf_mbx; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dmae_params {void* dst_vfid; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {void* status; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
struct TYPE_10__ {TYPE_2__ default_resp; } ;
struct TYPE_8__ {scalar_t__ reply_address; } ;
struct TYPE_9__ {TYPE_3__ first_tlv; } ;

/* Variables and functions */
 scalar_t__ GTT_BAR0_MAP_REG_USDM_RAM ; 
 int /*<<< orphan*/  QED_DMAE_FLAG_VF_DST ; 
 int /*<<< orphan*/  REG_WR (struct qed_hwfn*,scalar_t__,int) ; 
 scalar_t__ USTORM_VF_PF_CHANNEL_READY_OFFSET (void*) ; 
 int /*<<< orphan*/  memset (struct qed_dmae_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_dmae_host2host (struct qed_hwfn*,struct qed_ptt*,scalar_t__,scalar_t__,int,struct qed_dmae_params*) ; 
 int /*<<< orphan*/  qed_dp_tlv_list (struct qed_hwfn*,TYPE_5__*) ; 

__attribute__((used)) static void qed_iov_send_response(struct qed_hwfn *p_hwfn,
				  struct qed_ptt *p_ptt,
				  struct qed_vf_info *p_vf,
				  u16 length, u8 status)
{
	struct qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	struct qed_dmae_params params;
	u8 eng_vf_id;

	mbx->reply_virt->default_resp.hdr.status = status;

	qed_dp_tlv_list(p_hwfn, mbx->reply_virt);

	eng_vf_id = p_vf->abs_vf_id;

	memset(&params, 0, sizeof(struct qed_dmae_params));
	params.flags = QED_DMAE_FLAG_VF_DST;
	params.dst_vfid = eng_vf_id;

	qed_dmae_host2host(p_hwfn, p_ptt, mbx->reply_phys + sizeof(u64),
			   mbx->req_virt->first_tlv.reply_address +
			   sizeof(u64),
			   (sizeof(union pfvf_tlvs) - sizeof(u64)) / 4,
			   &params);

	/* Once PF copies the rc to the VF, the latter can continue
	 * and send an additional message. So we have to make sure the
	 * channel would be re-set to ready prior to that.
	 */
	REG_WR(p_hwfn,
	       GTT_BAR0_MAP_REG_USDM_RAM +
	       USTORM_VF_PF_CHANNEL_READY_OFFSET(eng_vf_id), 1);

	qed_dmae_host2host(p_hwfn, p_ptt, mbx->reply_phys,
			   mbx->req_virt->first_tlv.reply_address,
			   sizeof(u64) / 4, &params);
}