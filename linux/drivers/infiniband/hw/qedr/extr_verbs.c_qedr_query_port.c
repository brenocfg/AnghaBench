#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct qedr_dev {int /*<<< orphan*/  ibdev; TYPE_2__* ndev; int /*<<< orphan*/  rdma_ctx; TYPE_1__* ops; } ;
struct qed_rdma_port {scalar_t__ port_state; int /*<<< orphan*/  max_msg_size; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  pkey_bad_counter; } ;
struct ib_port_attr {int ip_gids; int gid_tbl_len; int pkey_tbl_len; int max_vl_num; int /*<<< orphan*/  max_msg_sz; int /*<<< orphan*/  active_width; int /*<<< orphan*/  active_speed; scalar_t__ qkey_viol_cntr; int /*<<< orphan*/  bad_pkey_cntr; scalar_t__ sm_sl; scalar_t__ sm_lid; scalar_t__ lmc; scalar_t__ lid; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  state; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtu; } ;
struct TYPE_3__ {struct qed_rdma_port* (* rdma_query_port ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IB_MTU_4096 ; 
 int /*<<< orphan*/  IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_PORT_DOWN ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_DISABLED ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_LINK_UP ; 
 int QEDR_MAX_SGID ; 
 int QEDR_ROCE_PKEY_TABLE_LEN ; 
 scalar_t__ QED_RDMA_PORT_UP ; 
 int /*<<< orphan*/  get_link_speed_and_width (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct qedr_dev* get_qedr_dev (struct ib_device*) ; 
 int /*<<< orphan*/  iboe_get_mtu (int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_protocol_iwarp (int /*<<< orphan*/ *,int) ; 
 struct qed_rdma_port* stub1 (int /*<<< orphan*/ ) ; 

int qedr_query_port(struct ib_device *ibdev, u8 port, struct ib_port_attr *attr)
{
	struct qedr_dev *dev;
	struct qed_rdma_port *rdma_port;

	dev = get_qedr_dev(ibdev);

	if (!dev->rdma_ctx) {
		DP_ERR(dev, "rdma_ctx is NULL\n");
		return -EINVAL;
	}

	rdma_port = dev->ops->rdma_query_port(dev->rdma_ctx);

	/* *attr being zeroed by the caller, avoid zeroing it here */
	if (rdma_port->port_state == QED_RDMA_PORT_UP) {
		attr->state = IB_PORT_ACTIVE;
		attr->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	} else {
		attr->state = IB_PORT_DOWN;
		attr->phys_state = IB_PORT_PHYS_STATE_DISABLED;
	}
	attr->max_mtu = IB_MTU_4096;
	attr->active_mtu = iboe_get_mtu(dev->ndev->mtu);
	attr->lid = 0;
	attr->lmc = 0;
	attr->sm_lid = 0;
	attr->sm_sl = 0;
	attr->ip_gids = true;
	if (rdma_protocol_iwarp(&dev->ibdev, 1)) {
		attr->gid_tbl_len = 1;
		attr->pkey_tbl_len = 1;
	} else {
		attr->gid_tbl_len = QEDR_MAX_SGID;
		attr->pkey_tbl_len = QEDR_ROCE_PKEY_TABLE_LEN;
	}
	attr->bad_pkey_cntr = rdma_port->pkey_bad_counter;
	attr->qkey_viol_cntr = 0;
	get_link_speed_and_width(rdma_port->link_speed,
				 &attr->active_speed, &attr->active_width);
	attr->max_msg_sz = rdma_port->max_msg_size;
	attr->max_vl_num = 4;

	return 0;
}