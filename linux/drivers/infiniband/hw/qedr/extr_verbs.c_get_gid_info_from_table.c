#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_7__ {void** dwords; void* ipv4_addr; int /*<<< orphan*/ * bytes; } ;
struct qed_rdma_modify_qp_in_params {int /*<<< orphan*/  vlan_id; TYPE_3__ dgid; TYPE_3__ sgid; int /*<<< orphan*/  roce_mode; int /*<<< orphan*/  modify_flags; } ;
struct ib_qp_attr {int /*<<< orphan*/  ah_attr; } ;
struct ib_qp {int dummy; } ;
struct TYPE_6__ {struct TYPE_6__* raw; } ;
struct ib_global_route {TYPE_2__ dgid; struct ib_gid_attr* sgid_attr; } ;
struct TYPE_5__ {TYPE_2__* raw; } ;
struct ib_gid_attr {TYPE_1__ gid; } ;
typedef  enum rdma_network_type { ____Placeholder_rdma_network_type } rdma_network_type ;

/* Variables and functions */
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_ROCE_MODE ; 
#define  RDMA_NETWORK_IB 130 
#define  RDMA_NETWORK_IPV4 129 
#define  RDMA_NETWORK_IPV6 128 
 int /*<<< orphan*/  ROCE_V1 ; 
 int /*<<< orphan*/  ROCE_V2_IPV4 ; 
 int /*<<< orphan*/  ROCE_V2_IPV6 ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VLAN_CFI_MASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 void* ntohl (void*) ; 
 void* qedr_get_ipv4_from_gid (TYPE_2__*) ; 
 struct ib_global_route* rdma_ah_read_grh (int /*<<< orphan*/ *) ; 
 int rdma_gid_attr_network_type (struct ib_gid_attr const*) ; 
 int rdma_read_gid_l2_fields (struct ib_gid_attr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_gid_info_from_table(struct ib_qp *ibqp,
					  struct ib_qp_attr *attr,
					  int attr_mask,
					  struct qed_rdma_modify_qp_in_params
					  *qp_params)
{
	const struct ib_gid_attr *gid_attr;
	enum rdma_network_type nw_type;
	const struct ib_global_route *grh = rdma_ah_read_grh(&attr->ah_attr);
	u32 ipv4_addr;
	int ret;
	int i;

	gid_attr = grh->sgid_attr;
	ret = rdma_read_gid_l2_fields(gid_attr, &qp_params->vlan_id, NULL);
	if (ret)
		return ret;

	nw_type = rdma_gid_attr_network_type(gid_attr);
	switch (nw_type) {
	case RDMA_NETWORK_IPV6:
		memcpy(&qp_params->sgid.bytes[0], &gid_attr->gid.raw[0],
		       sizeof(qp_params->sgid));
		memcpy(&qp_params->dgid.bytes[0],
		       &grh->dgid,
		       sizeof(qp_params->dgid));
		qp_params->roce_mode = ROCE_V2_IPV6;
		SET_FIELD(qp_params->modify_flags,
			  QED_ROCE_MODIFY_QP_VALID_ROCE_MODE, 1);
		break;
	case RDMA_NETWORK_IB:
		memcpy(&qp_params->sgid.bytes[0], &gid_attr->gid.raw[0],
		       sizeof(qp_params->sgid));
		memcpy(&qp_params->dgid.bytes[0],
		       &grh->dgid,
		       sizeof(qp_params->dgid));
		qp_params->roce_mode = ROCE_V1;
		break;
	case RDMA_NETWORK_IPV4:
		memset(&qp_params->sgid, 0, sizeof(qp_params->sgid));
		memset(&qp_params->dgid, 0, sizeof(qp_params->dgid));
		ipv4_addr = qedr_get_ipv4_from_gid(gid_attr->gid.raw);
		qp_params->sgid.ipv4_addr = ipv4_addr;
		ipv4_addr =
		    qedr_get_ipv4_from_gid(grh->dgid.raw);
		qp_params->dgid.ipv4_addr = ipv4_addr;
		SET_FIELD(qp_params->modify_flags,
			  QED_ROCE_MODIFY_QP_VALID_ROCE_MODE, 1);
		qp_params->roce_mode = ROCE_V2_IPV4;
		break;
	}

	for (i = 0; i < 4; i++) {
		qp_params->sgid.dwords[i] = ntohl(qp_params->sgid.dwords[i]);
		qp_params->dgid.dwords[i] = ntohl(qp_params->dgid.dwords[i]);
	}

	if (qp_params->vlan_id >= VLAN_CFI_MASK)
		qp_params->vlan_id = 0;

	return 0;
}