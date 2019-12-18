#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {struct ib_gid_attr* sgid_attr; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_1__ grh; } ;
struct ib_qp_attr {size_t port_num; TYPE_5__ ah_attr; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_11__ {int /*<<< orphan*/  raw; } ;
struct ib_global_route {int sgid_index; int hop_limit; int traffic_class; int flow_label; TYPE_4__ dgid; } ;
struct ib_gid_attr {scalar_t__ gid_type; } ;
struct hns_roce_v2_qp_context {int /*<<< orphan*/  byte_28_at_fl; int /*<<< orphan*/  dgid; int /*<<< orphan*/  byte_24_mtu_tc; int /*<<< orphan*/  byte_20_smac_sgid_idx; int /*<<< orphan*/  byte_52_udpspn_dmac; int /*<<< orphan*/  byte_168_irrl_idx; int /*<<< orphan*/  byte_76_srqn_op_en; } ;
struct hns_roce_qp {size_t port; int sl; } ;
struct TYPE_9__ {int* gid_table_len; } ;
struct hns_roce_dev {TYPE_3__* pci_dev; int /*<<< orphan*/  dev; TYPE_2__ caps; int /*<<< orphan*/  ib_dev; } ;
struct TYPE_10__ {int revision; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_AH_GRH ; 
 scalar_t__ IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 int IB_QP_PORT ; 
 scalar_t__ RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_SQ_VLAN_EN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SGID_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SGID_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_HOP_LIMIT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_HOP_LIMIT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_TC_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_TC_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_VLAN_ID_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_VLAN_ID_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_FL_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_FL_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_SL_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_SL_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_52_UDPSPN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_52_UDPSPN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_RQ_VLAN_EN_S ; 
 scalar_t__ VLAN_CFI_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rdma_ah_get_ah_flags (TYPE_5__*) ; 
 int rdma_ah_get_sl (TYPE_5__*) ; 
 struct ib_global_route* rdma_ah_read_grh (TYPE_5__*) ; 
 scalar_t__ rdma_cap_eth_ah (int /*<<< orphan*/ *,size_t) ; 
 int rdma_read_gid_l2_fields (struct ib_gid_attr const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

__attribute__((used)) static int hns_roce_v2_set_path(struct ib_qp *ibqp,
				const struct ib_qp_attr *attr,
				int attr_mask,
				struct hns_roce_v2_qp_context *context,
				struct hns_roce_v2_qp_context *qpc_mask)
{
	const struct ib_global_route *grh = rdma_ah_read_grh(&attr->ah_attr);
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	const struct ib_gid_attr *gid_attr = NULL;
	int is_roce_protocol;
	bool is_udp = false;
	u16 vlan = 0xffff;
	u8 ib_port;
	u8 hr_port;
	int ret;

	ib_port = (attr_mask & IB_QP_PORT) ? attr->port_num : hr_qp->port + 1;
	hr_port = ib_port - 1;
	is_roce_protocol = rdma_cap_eth_ah(&hr_dev->ib_dev, ib_port) &&
			   rdma_ah_get_ah_flags(&attr->ah_attr) & IB_AH_GRH;

	if (is_roce_protocol) {
		gid_attr = attr->ah_attr.grh.sgid_attr;
		ret = rdma_read_gid_l2_fields(gid_attr, &vlan, NULL);
		if (ret)
			return ret;

		if (gid_attr)
			is_udp = (gid_attr->gid_type ==
				 IB_GID_TYPE_ROCE_UDP_ENCAP);
	}

	if (vlan < VLAN_CFI_MASK) {
		roce_set_bit(context->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_RQ_VLAN_EN_S, 1);
		roce_set_bit(qpc_mask->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_RQ_VLAN_EN_S, 0);
		roce_set_bit(context->byte_168_irrl_idx,
			     V2_QPC_BYTE_168_SQ_VLAN_EN_S, 1);
		roce_set_bit(qpc_mask->byte_168_irrl_idx,
			     V2_QPC_BYTE_168_SQ_VLAN_EN_S, 0);
	}

	roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_VLAN_ID_M,
		       V2_QPC_BYTE_24_VLAN_ID_S, vlan);
	roce_set_field(qpc_mask->byte_24_mtu_tc, V2_QPC_BYTE_24_VLAN_ID_M,
		       V2_QPC_BYTE_24_VLAN_ID_S, 0);

	if (grh->sgid_index >= hr_dev->caps.gid_table_len[hr_port]) {
		dev_err(hr_dev->dev, "sgid_index(%u) too large. max is %d\n",
			grh->sgid_index, hr_dev->caps.gid_table_len[hr_port]);
		return -EINVAL;
	}

	if (attr->ah_attr.type != RDMA_AH_ATTR_TYPE_ROCE) {
		dev_err(hr_dev->dev, "ah attr is not RDMA roce type\n");
		return -EINVAL;
	}

	roce_set_field(context->byte_52_udpspn_dmac, V2_QPC_BYTE_52_UDPSPN_M,
		       V2_QPC_BYTE_52_UDPSPN_S,
		       is_udp ? 0x12b7 : 0);

	roce_set_field(qpc_mask->byte_52_udpspn_dmac, V2_QPC_BYTE_52_UDPSPN_M,
		       V2_QPC_BYTE_52_UDPSPN_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGID_IDX_M, V2_QPC_BYTE_20_SGID_IDX_S,
		       grh->sgid_index);

	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGID_IDX_M, V2_QPC_BYTE_20_SGID_IDX_S, 0);

	roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_HOP_LIMIT_M,
		       V2_QPC_BYTE_24_HOP_LIMIT_S, grh->hop_limit);
	roce_set_field(qpc_mask->byte_24_mtu_tc, V2_QPC_BYTE_24_HOP_LIMIT_M,
		       V2_QPC_BYTE_24_HOP_LIMIT_S, 0);

	if (hr_dev->pci_dev->revision == 0x21 && is_udp)
		roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_TC_M,
			       V2_QPC_BYTE_24_TC_S, grh->traffic_class >> 2);
	else
		roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_TC_M,
			       V2_QPC_BYTE_24_TC_S, grh->traffic_class);
	roce_set_field(qpc_mask->byte_24_mtu_tc, V2_QPC_BYTE_24_TC_M,
		       V2_QPC_BYTE_24_TC_S, 0);
	roce_set_field(context->byte_28_at_fl, V2_QPC_BYTE_28_FL_M,
		       V2_QPC_BYTE_28_FL_S, grh->flow_label);
	roce_set_field(qpc_mask->byte_28_at_fl, V2_QPC_BYTE_28_FL_M,
		       V2_QPC_BYTE_28_FL_S, 0);
	memcpy(context->dgid, grh->dgid.raw, sizeof(grh->dgid.raw));
	memset(qpc_mask->dgid, 0, sizeof(grh->dgid.raw));
	roce_set_field(context->byte_28_at_fl, V2_QPC_BYTE_28_SL_M,
		       V2_QPC_BYTE_28_SL_S, rdma_ah_get_sl(&attr->ah_attr));
	roce_set_field(qpc_mask->byte_28_at_fl, V2_QPC_BYTE_28_SL_M,
		       V2_QPC_BYTE_28_SL_S, 0);
	hr_qp->sl = rdma_ah_get_sl(&attr->ah_attr);

	return 0;
}