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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct qed_iov_vf_mbx {int /*<<< orphan*/ * offset; scalar_t__ reply_virt; } ;
struct qed_vf_info {struct qed_iov_vf_mbx vf_mbx; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct channel_list_end_tlv {int dummy; } ;

/* Variables and functions */
 int CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  qed_add_tlv (struct qed_hwfn*,int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  qed_iov_send_response (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_iov_prepare_resp(struct qed_hwfn *p_hwfn,
				 struct qed_ptt *p_ptt,
				 struct qed_vf_info *vf_info,
				 u16 type, u16 length, u8 status)
{
	struct qed_iov_vf_mbx *mbx = &vf_info->vf_mbx;

	mbx->offset = (u8 *)mbx->reply_virt;

	qed_add_tlv(p_hwfn, &mbx->offset, type, length);
	qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_LIST_END,
		    sizeof(struct channel_list_end_tlv));

	qed_iov_send_response(p_hwfn, p_ptt, vf_info, length, status);
}