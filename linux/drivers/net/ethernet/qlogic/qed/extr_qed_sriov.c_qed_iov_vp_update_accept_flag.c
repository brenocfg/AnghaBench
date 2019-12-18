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
typedef  int u16 ;
struct vfpf_vport_update_accept_param_tlv {int /*<<< orphan*/  tx_accept_filter; int /*<<< orphan*/  update_tx_mode; int /*<<< orphan*/  rx_accept_filter; int /*<<< orphan*/  update_rx_mode; } ;
struct qed_filter_accept_flags {int /*<<< orphan*/  tx_accept_filter; int /*<<< orphan*/  update_tx_mode_config; int /*<<< orphan*/  rx_accept_filter; int /*<<< orphan*/  update_rx_mode_config; } ;
struct qed_sp_vport_update_params {struct qed_filter_accept_flags accept_flags; } ;
struct qed_iov_vf_mbx {int /*<<< orphan*/  req_virt; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM ; 
 int QED_IOV_VP_UPDATE_ACCEPT_PARAM ; 
 scalar_t__ qed_iov_search_list_tlvs (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qed_iov_vp_update_accept_flag(struct qed_hwfn *p_hwfn,
			      struct qed_sp_vport_update_params *p_data,
			      struct qed_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
{
	struct qed_filter_accept_flags *p_flags = &p_data->accept_flags;
	struct vfpf_vport_update_accept_param_tlv *p_accept_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM;

	p_accept_tlv = (struct vfpf_vport_update_accept_param_tlv *)
	    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt, tlv);
	if (!p_accept_tlv)
		return;

	p_flags->update_rx_mode_config = p_accept_tlv->update_rx_mode;
	p_flags->rx_accept_filter = p_accept_tlv->rx_accept_filter;
	p_flags->update_tx_mode_config = p_accept_tlv->update_tx_mode;
	p_flags->tx_accept_filter = p_accept_tlv->tx_accept_filter;
	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_ACCEPT_PARAM;
}