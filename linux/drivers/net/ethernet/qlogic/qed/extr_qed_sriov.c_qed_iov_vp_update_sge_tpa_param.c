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
struct vfpf_vport_update_sge_tpa_tlv {int update_sge_tpa_flags; int sge_tpa_flags; int /*<<< orphan*/  max_buffers_per_cqe; int /*<<< orphan*/  tpa_min_size_to_cont; int /*<<< orphan*/  tpa_min_size_to_start; int /*<<< orphan*/  tpa_max_size; int /*<<< orphan*/  tpa_max_aggs_num; } ;
struct qed_vf_info {int dummy; } ;
struct qed_sp_vport_update_params {struct qed_sge_tpa_params* sge_tpa_params; } ;
struct qed_sge_tpa_params {int update_tpa_en_flg; int update_tpa_param_flg; int tpa_ipv4_en_flg; int tpa_ipv6_en_flg; int tpa_pkt_split_flg; int tpa_hdr_data_split_flg; int tpa_gro_consistent_flg; int /*<<< orphan*/  max_buffers_per_cqe; int /*<<< orphan*/  tpa_min_size_to_cont; int /*<<< orphan*/  tpa_min_size_to_start; int /*<<< orphan*/  tpa_max_size; int /*<<< orphan*/  tpa_max_aggs_num; } ;
struct qed_iov_vf_mbx {int /*<<< orphan*/  req_virt; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int CHANNEL_TLV_VPORT_UPDATE_SGE_TPA ; 
 int QED_IOV_VP_UPDATE_SGE_TPA ; 
 int VFPF_TPA_GRO_CONSIST_FLAG ; 
 int VFPF_TPA_HDR_DATA_SPLIT_FLAG ; 
 int VFPF_TPA_IPV4_EN_FLAG ; 
 int VFPF_TPA_IPV6_EN_FLAG ; 
 int VFPF_TPA_PKT_SPLIT_FLAG ; 
 int VFPF_UPDATE_TPA_EN_FLAG ; 
 int VFPF_UPDATE_TPA_PARAM_FLAG ; 
 int /*<<< orphan*/  memset (struct qed_sge_tpa_params*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qed_iov_search_list_tlvs (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qed_iov_vp_update_sge_tpa_param(struct qed_hwfn *p_hwfn,
				struct qed_vf_info *vf,
				struct qed_sp_vport_update_params *p_data,
				struct qed_sge_tpa_params *p_sge_tpa,
				struct qed_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
{
	struct vfpf_vport_update_sge_tpa_tlv *p_sge_tpa_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_SGE_TPA;

	p_sge_tpa_tlv = (struct vfpf_vport_update_sge_tpa_tlv *)
	    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt, tlv);

	if (!p_sge_tpa_tlv) {
		p_data->sge_tpa_params = NULL;
		return;
	}

	memset(p_sge_tpa, 0, sizeof(struct qed_sge_tpa_params));

	p_sge_tpa->update_tpa_en_flg =
	    !!(p_sge_tpa_tlv->update_sge_tpa_flags & VFPF_UPDATE_TPA_EN_FLAG);
	p_sge_tpa->update_tpa_param_flg =
	    !!(p_sge_tpa_tlv->update_sge_tpa_flags &
		VFPF_UPDATE_TPA_PARAM_FLAG);

	p_sge_tpa->tpa_ipv4_en_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_IPV4_EN_FLAG);
	p_sge_tpa->tpa_ipv6_en_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_IPV6_EN_FLAG);
	p_sge_tpa->tpa_pkt_split_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_PKT_SPLIT_FLAG);
	p_sge_tpa->tpa_hdr_data_split_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_HDR_DATA_SPLIT_FLAG);
	p_sge_tpa->tpa_gro_consistent_flg =
	    !!(p_sge_tpa_tlv->sge_tpa_flags & VFPF_TPA_GRO_CONSIST_FLAG);

	p_sge_tpa->tpa_max_aggs_num = p_sge_tpa_tlv->tpa_max_aggs_num;
	p_sge_tpa->tpa_max_size = p_sge_tpa_tlv->tpa_max_size;
	p_sge_tpa->tpa_min_size_to_start = p_sge_tpa_tlv->tpa_min_size_to_start;
	p_sge_tpa->tpa_min_size_to_cont = p_sge_tpa_tlv->tpa_min_size_to_cont;
	p_sge_tpa->max_buffers_per_cqe = p_sge_tpa_tlv->max_buffers_per_cqe;

	p_data->sge_tpa_params = p_sge_tpa;

	*tlvs_mask |= 1 << QED_IOV_VP_UPDATE_SGE_TPA;
}