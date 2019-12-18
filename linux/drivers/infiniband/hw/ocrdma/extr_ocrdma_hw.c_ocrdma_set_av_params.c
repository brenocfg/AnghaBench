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
typedef  int u8 ;
typedef  int u16 ;
struct sockaddr_in6 {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_7__ {struct ib_gid_attr* sgid_attr; } ;
struct rdma_ah_attr {TYPE_2__ grh; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct ocrdma_qp {int /*<<< orphan*/  sgid_idx; TYPE_1__ ibqp; } ;
struct TYPE_9__ {int tclass_sq_psn; int rnt_rc_sl_fl; int hop_lmt_rq_psn; int dmac_b0_to_b3; int vlan_dmac_b4_to_b5; int max_sge_recv_flags; int /*<<< orphan*/ * sgid; int /*<<< orphan*/ * dgid; } ;
struct ocrdma_modify_qp {TYPE_4__ params; int /*<<< orphan*/  flags; } ;
struct ocrdma_dev {int sl; int /*<<< orphan*/  id; scalar_t__ pfc_state; int /*<<< orphan*/  update_sl; } ;
struct ib_qp_attr {struct rdma_ah_attr ah_attr; } ;
struct TYPE_10__ {int /*<<< orphan*/ * raw; } ;
struct ib_global_route {int traffic_class; int flow_label; int hop_limit; TYPE_5__ dgid; int /*<<< orphan*/  sgid_index; } ;
struct ib_gid_attr {TYPE_5__ gid; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_AH_GRH ; 
 int OCRDMA_QP_PARAMS_FLAGS_L3_TYPE_MASK ; 
 int OCRDMA_QP_PARAMS_FLAGS_L3_TYPE_SHIFT ; 
 int OCRDMA_QP_PARAMS_FLOW_LABEL_MASK ; 
 int OCRDMA_QP_PARAMS_HOP_LMT_SHIFT ; 
 int OCRDMA_QP_PARAMS_SL_SHIFT ; 
 int OCRDMA_QP_PARAMS_TCLASS_SHIFT ; 
 int OCRDMA_QP_PARAMS_VLAN_SHIFT ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_FLOW_LBL_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_VLAN_EN_VALID ; 
 int RDMA_NETWORK_IPV4 ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocrdma_cpu_to_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocrdma_init_service_level (struct ocrdma_dev*) ; 
 int ocrdma_resolve_dmac (struct ocrdma_dev*,struct rdma_ah_attr*,int*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_gid2ip (struct sockaddr*,TYPE_5__*) ; 
 int rdma_gid_attr_network_type (struct ib_gid_attr const*) ; 
 int rdma_read_gid_l2_fields (struct ib_gid_attr const*,int*,int*) ; 

__attribute__((used)) static int ocrdma_set_av_params(struct ocrdma_qp *qp,
				struct ocrdma_modify_qp *cmd,
				struct ib_qp_attr *attrs,
				int attr_mask)
{
	int status;
	struct rdma_ah_attr *ah_attr = &attrs->ah_attr;
	const struct ib_gid_attr *sgid_attr;
	u16 vlan_id = 0xFFFF;
	u8 mac_addr[6], hdr_type;
	union {
		struct sockaddr_in  _sockaddr_in;
		struct sockaddr_in6 _sockaddr_in6;
	} sgid_addr, dgid_addr;
	struct ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);
	const struct ib_global_route *grh;

	if ((rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) == 0)
		return -EINVAL;
	grh = rdma_ah_read_grh(ah_attr);
	if (atomic_cmpxchg(&dev->update_sl, 1, 0))
		ocrdma_init_service_level(dev);
	cmd->params.tclass_sq_psn |=
	    (grh->traffic_class << OCRDMA_QP_PARAMS_TCLASS_SHIFT);
	cmd->params.rnt_rc_sl_fl |=
	    (grh->flow_label & OCRDMA_QP_PARAMS_FLOW_LABEL_MASK);
	cmd->params.rnt_rc_sl_fl |= (rdma_ah_get_sl(ah_attr) <<
				     OCRDMA_QP_PARAMS_SL_SHIFT);
	cmd->params.hop_lmt_rq_psn |=
	    (grh->hop_limit << OCRDMA_QP_PARAMS_HOP_LMT_SHIFT);
	cmd->flags |= OCRDMA_QP_PARA_FLOW_LBL_VALID;

	/* GIDs */
	memcpy(&cmd->params.dgid[0], &grh->dgid.raw[0],
	       sizeof(cmd->params.dgid));

	sgid_attr = ah_attr->grh.sgid_attr;
	status = rdma_read_gid_l2_fields(sgid_attr, &vlan_id, &mac_addr[0]);
	if (status)
		return status;

	qp->sgid_idx = grh->sgid_index;
	memcpy(&cmd->params.sgid[0], &sgid_attr->gid.raw[0],
	       sizeof(cmd->params.sgid));
	status = ocrdma_resolve_dmac(dev, ah_attr, &mac_addr[0]);
	if (status)
		return status;

	cmd->params.dmac_b0_to_b3 = mac_addr[0] | (mac_addr[1] << 8) |
				(mac_addr[2] << 16) | (mac_addr[3] << 24);

	hdr_type = rdma_gid_attr_network_type(sgid_attr);
	if (hdr_type == RDMA_NETWORK_IPV4) {
		rdma_gid2ip((struct sockaddr *)&sgid_addr, &sgid_attr->gid);
		rdma_gid2ip((struct sockaddr *)&dgid_addr, &grh->dgid);
		memcpy(&cmd->params.dgid[0],
		       &dgid_addr._sockaddr_in.sin_addr.s_addr, 4);
		memcpy(&cmd->params.sgid[0],
		       &sgid_addr._sockaddr_in.sin_addr.s_addr, 4);
	}
	/* convert them to LE format. */
	ocrdma_cpu_to_le32(&cmd->params.dgid[0], sizeof(cmd->params.dgid));
	ocrdma_cpu_to_le32(&cmd->params.sgid[0], sizeof(cmd->params.sgid));
	cmd->params.vlan_dmac_b4_to_b5 = mac_addr[4] | (mac_addr[5] << 8);

	if (vlan_id == 0xFFFF)
		vlan_id = 0;
	if (vlan_id || dev->pfc_state) {
		if (!vlan_id) {
			pr_err("ocrdma%d:Using VLAN with PFC is recommended\n",
			       dev->id);
			pr_err("ocrdma%d:Using VLAN 0 for this connection\n",
			       dev->id);
		}
		cmd->params.vlan_dmac_b4_to_b5 |=
		    vlan_id << OCRDMA_QP_PARAMS_VLAN_SHIFT;
		cmd->flags |= OCRDMA_QP_PARA_VLAN_EN_VALID;
		cmd->params.rnt_rc_sl_fl |=
			(dev->sl & 0x07) << OCRDMA_QP_PARAMS_SL_SHIFT;
	}
	cmd->params.max_sge_recv_flags |= ((hdr_type <<
					OCRDMA_QP_PARAMS_FLAGS_L3_TYPE_SHIFT) &
					OCRDMA_QP_PARAMS_FLAGS_L3_TYPE_MASK);
	return 0;
}