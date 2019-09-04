#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct device* parent; } ;
struct ib_device {int uverbs_abi_ver; unsigned long long uverbs_cmd_mask; unsigned long long uverbs_ex_cmd_mask; int /*<<< orphan*/  driver_id; int /*<<< orphan*/  disassociate_ucontext; int /*<<< orphan*/  get_port_immutable; int /*<<< orphan*/  rereg_user_mr; int /*<<< orphan*/  dereg_mr; int /*<<< orphan*/  reg_user_mr; int /*<<< orphan*/  get_dma_mr; int /*<<< orphan*/  poll_cq; int /*<<< orphan*/  req_notify_cq; int /*<<< orphan*/  destroy_cq; int /*<<< orphan*/  modify_cq; int /*<<< orphan*/  create_cq; int /*<<< orphan*/  post_recv; int /*<<< orphan*/  post_send; int /*<<< orphan*/  destroy_qp; int /*<<< orphan*/  query_qp; int /*<<< orphan*/  modify_qp; int /*<<< orphan*/  create_qp; int /*<<< orphan*/  destroy_ah; int /*<<< orphan*/  query_ah; int /*<<< orphan*/  create_ah; int /*<<< orphan*/  dealloc_pd; int /*<<< orphan*/  alloc_pd; int /*<<< orphan*/  mmap; int /*<<< orphan*/  dealloc_ucontext; int /*<<< orphan*/  alloc_ucontext; int /*<<< orphan*/  query_pkey; int /*<<< orphan*/  del_gid; int /*<<< orphan*/  add_gid; int /*<<< orphan*/  get_netdev; int /*<<< orphan*/  get_link_layer; int /*<<< orphan*/  modify_port; int /*<<< orphan*/  query_port; int /*<<< orphan*/  query_device; int /*<<< orphan*/  modify_device; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  local_dma_lkey; int /*<<< orphan*/  phys_port_cnt; TYPE_1__ dev; int /*<<< orphan*/  node_type; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  notifier_call; } ;
struct hns_roce_ib_iboe {TYPE_4__ nb; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  reserved_lkey; int /*<<< orphan*/  num_ports; } ;
struct hns_roce_dev {int active; TYPE_3__ caps; TYPE_2__* hw; struct ib_device ib_dev; struct hns_roce_ib_iboe iboe; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  poll_cq; int /*<<< orphan*/  req_notify_cq; int /*<<< orphan*/  modify_cq; int /*<<< orphan*/  post_recv; int /*<<< orphan*/  post_send; int /*<<< orphan*/  destroy_qp; int /*<<< orphan*/  query_qp; } ;

/* Variables and functions */
 int HNS_ROCE_CAP_FLAG_REREG_MR ; 
 int /*<<< orphan*/  IB_DEVICE_NAME_MAX ; 
 unsigned long long IB_USER_VERBS_CMD_ALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_QP ; 
 unsigned long long IB_USER_VERBS_CMD_DEALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_DEREG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_GET_CONTEXT ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_DEVICE ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_PORT ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_REG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_REREG_MR ; 
 unsigned long long IB_USER_VERBS_EX_CMD_MODIFY_CQ ; 
 int /*<<< orphan*/  RDMA_DRIVER_HNS ; 
 int /*<<< orphan*/  RDMA_NODE_IB_CA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  hns_roce_add_gid ; 
 int /*<<< orphan*/  hns_roce_alloc_pd ; 
 int /*<<< orphan*/  hns_roce_alloc_ucontext ; 
 int /*<<< orphan*/  hns_roce_create_ah ; 
 int /*<<< orphan*/  hns_roce_create_qp ; 
 int /*<<< orphan*/  hns_roce_dealloc_pd ; 
 int /*<<< orphan*/  hns_roce_dealloc_ucontext ; 
 int /*<<< orphan*/  hns_roce_del_gid ; 
 int /*<<< orphan*/  hns_roce_dereg_mr ; 
 int /*<<< orphan*/  hns_roce_destroy_ah ; 
 int /*<<< orphan*/  hns_roce_disassociate_ucontext ; 
 int /*<<< orphan*/  hns_roce_get_dma_mr ; 
 int /*<<< orphan*/  hns_roce_get_link_layer ; 
 int /*<<< orphan*/  hns_roce_get_netdev ; 
 int /*<<< orphan*/  hns_roce_ib_create_cq ; 
 int /*<<< orphan*/  hns_roce_ib_destroy_cq ; 
 int /*<<< orphan*/  hns_roce_mmap ; 
 int /*<<< orphan*/  hns_roce_modify_device ; 
 int /*<<< orphan*/  hns_roce_modify_port ; 
 int /*<<< orphan*/  hns_roce_modify_qp ; 
 int /*<<< orphan*/  hns_roce_netdev_event ; 
 int /*<<< orphan*/  hns_roce_port_immutable ; 
 int /*<<< orphan*/  hns_roce_query_ah ; 
 int /*<<< orphan*/  hns_roce_query_device ; 
 int /*<<< orphan*/  hns_roce_query_pkey ; 
 int /*<<< orphan*/  hns_roce_query_port ; 
 int /*<<< orphan*/  hns_roce_reg_user_mr ; 
 int /*<<< orphan*/  hns_roce_rereg_user_mr ; 
 int hns_roce_setup_mtu_mac (struct hns_roce_dev*) ; 
 int ib_register_device (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (struct ib_device*) ; 
 int register_netdevice_notifier (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_register_device(struct hns_roce_dev *hr_dev)
{
	int ret;
	struct hns_roce_ib_iboe *iboe = NULL;
	struct ib_device *ib_dev = NULL;
	struct device *dev = hr_dev->dev;

	iboe = &hr_dev->iboe;
	spin_lock_init(&iboe->lock);

	ib_dev = &hr_dev->ib_dev;
	strlcpy(ib_dev->name, "hns_%d", IB_DEVICE_NAME_MAX);

	ib_dev->owner			= THIS_MODULE;
	ib_dev->node_type		= RDMA_NODE_IB_CA;
	ib_dev->dev.parent		= dev;

	ib_dev->phys_port_cnt		= hr_dev->caps.num_ports;
	ib_dev->local_dma_lkey		= hr_dev->caps.reserved_lkey;
	ib_dev->num_comp_vectors	= hr_dev->caps.num_comp_vectors;
	ib_dev->uverbs_abi_ver		= 1;
	ib_dev->uverbs_cmd_mask		=
		(1ULL << IB_USER_VERBS_CMD_GET_CONTEXT) |
		(1ULL << IB_USER_VERBS_CMD_QUERY_DEVICE) |
		(1ULL << IB_USER_VERBS_CMD_QUERY_PORT) |
		(1ULL << IB_USER_VERBS_CMD_ALLOC_PD) |
		(1ULL << IB_USER_VERBS_CMD_DEALLOC_PD) |
		(1ULL << IB_USER_VERBS_CMD_REG_MR) |
		(1ULL << IB_USER_VERBS_CMD_DEREG_MR) |
		(1ULL << IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL) |
		(1ULL << IB_USER_VERBS_CMD_CREATE_CQ) |
		(1ULL << IB_USER_VERBS_CMD_DESTROY_CQ) |
		(1ULL << IB_USER_VERBS_CMD_CREATE_QP) |
		(1ULL << IB_USER_VERBS_CMD_MODIFY_QP) |
		(1ULL << IB_USER_VERBS_CMD_QUERY_QP) |
		(1ULL << IB_USER_VERBS_CMD_DESTROY_QP);

	ib_dev->uverbs_ex_cmd_mask |=
		(1ULL << IB_USER_VERBS_EX_CMD_MODIFY_CQ);

	/* HCA||device||port */
	ib_dev->modify_device		= hns_roce_modify_device;
	ib_dev->query_device		= hns_roce_query_device;
	ib_dev->query_port		= hns_roce_query_port;
	ib_dev->modify_port		= hns_roce_modify_port;
	ib_dev->get_link_layer		= hns_roce_get_link_layer;
	ib_dev->get_netdev		= hns_roce_get_netdev;
	ib_dev->add_gid			= hns_roce_add_gid;
	ib_dev->del_gid			= hns_roce_del_gid;
	ib_dev->query_pkey		= hns_roce_query_pkey;
	ib_dev->alloc_ucontext		= hns_roce_alloc_ucontext;
	ib_dev->dealloc_ucontext	= hns_roce_dealloc_ucontext;
	ib_dev->mmap			= hns_roce_mmap;

	/* PD */
	ib_dev->alloc_pd		= hns_roce_alloc_pd;
	ib_dev->dealloc_pd		= hns_roce_dealloc_pd;

	/* AH */
	ib_dev->create_ah		= hns_roce_create_ah;
	ib_dev->query_ah		= hns_roce_query_ah;
	ib_dev->destroy_ah		= hns_roce_destroy_ah;

	/* QP */
	ib_dev->create_qp		= hns_roce_create_qp;
	ib_dev->modify_qp		= hns_roce_modify_qp;
	ib_dev->query_qp		= hr_dev->hw->query_qp;
	ib_dev->destroy_qp		= hr_dev->hw->destroy_qp;
	ib_dev->post_send		= hr_dev->hw->post_send;
	ib_dev->post_recv		= hr_dev->hw->post_recv;

	/* CQ */
	ib_dev->create_cq		= hns_roce_ib_create_cq;
	ib_dev->modify_cq		= hr_dev->hw->modify_cq;
	ib_dev->destroy_cq		= hns_roce_ib_destroy_cq;
	ib_dev->req_notify_cq		= hr_dev->hw->req_notify_cq;
	ib_dev->poll_cq			= hr_dev->hw->poll_cq;

	/* MR */
	ib_dev->get_dma_mr		= hns_roce_get_dma_mr;
	ib_dev->reg_user_mr		= hns_roce_reg_user_mr;
	ib_dev->dereg_mr		= hns_roce_dereg_mr;
	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_REREG_MR) {
		ib_dev->rereg_user_mr	= hns_roce_rereg_user_mr;
		ib_dev->uverbs_cmd_mask |= (1ULL << IB_USER_VERBS_CMD_REREG_MR);
	}

	/* OTHERS */
	ib_dev->get_port_immutable	= hns_roce_port_immutable;
	ib_dev->disassociate_ucontext	= hns_roce_disassociate_ucontext;

	ib_dev->driver_id = RDMA_DRIVER_HNS;
	ret = ib_register_device(ib_dev, NULL);
	if (ret) {
		dev_err(dev, "ib_register_device failed!\n");
		return ret;
	}

	ret = hns_roce_setup_mtu_mac(hr_dev);
	if (ret) {
		dev_err(dev, "setup_mtu_mac failed!\n");
		goto error_failed_setup_mtu_mac;
	}

	iboe->nb.notifier_call = hns_roce_netdev_event;
	ret = register_netdevice_notifier(&iboe->nb);
	if (ret) {
		dev_err(dev, "register_netdevice_notifier failed!\n");
		goto error_failed_setup_mtu_mac;
	}

	hr_dev->active = true;
	return 0;

error_failed_setup_mtu_mac:
	ib_unregister_device(ib_dev);

	return ret;
}