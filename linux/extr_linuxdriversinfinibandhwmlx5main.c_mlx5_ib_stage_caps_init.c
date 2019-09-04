#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long long uverbs_cmd_mask; unsigned long long uverbs_ex_cmd_mask; int /*<<< orphan*/  read_counters; int /*<<< orphan*/  destroy_counters; int /*<<< orphan*/  create_counters; int /*<<< orphan*/  driver_id; int /*<<< orphan*/  modify_flow_action_esp; int /*<<< orphan*/  destroy_flow_action; int /*<<< orphan*/  create_flow_action_esp; int /*<<< orphan*/  destroy_flow; int /*<<< orphan*/  create_flow; int /*<<< orphan*/  reg_dm_mr; int /*<<< orphan*/  dealloc_dm; int /*<<< orphan*/  alloc_dm; int /*<<< orphan*/  dealloc_xrcd; int /*<<< orphan*/  alloc_xrcd; int /*<<< orphan*/  dealloc_mw; int /*<<< orphan*/  alloc_mw; int /*<<< orphan*/  disassociate_ucontext; int /*<<< orphan*/  set_vf_guid; int /*<<< orphan*/  get_vf_stats; int /*<<< orphan*/  set_vf_link_state; int /*<<< orphan*/  get_vf_config; int /*<<< orphan*/  alloc_rdma_netdev; int /*<<< orphan*/  get_vector_affinity; int /*<<< orphan*/  get_dev_fw_str; int /*<<< orphan*/  check_mr_status; int /*<<< orphan*/  map_mr_sg; int /*<<< orphan*/  alloc_mr; int /*<<< orphan*/  process_mad; int /*<<< orphan*/  detach_mcast; int /*<<< orphan*/  attach_mcast; int /*<<< orphan*/  dereg_mr; int /*<<< orphan*/  rereg_user_mr; int /*<<< orphan*/  reg_user_mr; int /*<<< orphan*/  get_dma_mr; int /*<<< orphan*/  req_notify_cq; int /*<<< orphan*/  poll_cq; int /*<<< orphan*/  destroy_cq; int /*<<< orphan*/  resize_cq; int /*<<< orphan*/  modify_cq; int /*<<< orphan*/  create_cq; int /*<<< orphan*/  post_recv; int /*<<< orphan*/  post_send; int /*<<< orphan*/  drain_rq; int /*<<< orphan*/  drain_sq; int /*<<< orphan*/  destroy_qp; int /*<<< orphan*/  query_qp; int /*<<< orphan*/  modify_qp; int /*<<< orphan*/  create_qp; int /*<<< orphan*/  post_srq_recv; int /*<<< orphan*/  destroy_srq; int /*<<< orphan*/  query_srq; int /*<<< orphan*/  modify_srq; int /*<<< orphan*/  create_srq; int /*<<< orphan*/  destroy_ah; int /*<<< orphan*/  query_ah; int /*<<< orphan*/  create_ah; int /*<<< orphan*/  dealloc_pd; int /*<<< orphan*/  alloc_pd; int /*<<< orphan*/  mmap; int /*<<< orphan*/  dealloc_ucontext; int /*<<< orphan*/  alloc_ucontext; int /*<<< orphan*/  modify_port; int /*<<< orphan*/  modify_device; int /*<<< orphan*/  query_pkey; int /*<<< orphan*/  del_gid; int /*<<< orphan*/  add_gid; int /*<<< orphan*/  query_gid; int /*<<< orphan*/  get_link_layer; int /*<<< orphan*/  query_device; int /*<<< orphan*/  uverbs_abi_ver; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  lb_mutex; struct mlx5_core_dev* mdev; TYPE_1__ ib_dev; int /*<<< orphan*/  umr_fence; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 unsigned long long IB_USER_VERBS_CMD_ALLOC_MW ; 
 unsigned long long IB_USER_VERBS_CMD_ALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_ATTACH_MCAST ; 
 unsigned long long IB_USER_VERBS_CMD_CLOSE_XRCD ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_AH ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_QP ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_XSRQ ; 
 unsigned long long IB_USER_VERBS_CMD_DEALLOC_MW ; 
 unsigned long long IB_USER_VERBS_CMD_DEALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_DEREG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_AH ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_DETACH_MCAST ; 
 unsigned long long IB_USER_VERBS_CMD_GET_CONTEXT ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_OPEN_QP ; 
 unsigned long long IB_USER_VERBS_CMD_OPEN_XRCD ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_DEVICE ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_PORT ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_REG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_REREG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_RESIZE_CQ ; 
 unsigned long long IB_USER_VERBS_EX_CMD_CREATE_CQ ; 
 unsigned long long IB_USER_VERBS_EX_CMD_CREATE_FLOW ; 
 unsigned long long IB_USER_VERBS_EX_CMD_CREATE_QP ; 
 unsigned long long IB_USER_VERBS_EX_CMD_DESTROY_FLOW ; 
 unsigned long long IB_USER_VERBS_EX_CMD_MODIFY_CQ ; 
 unsigned long long IB_USER_VERBS_EX_CMD_MODIFY_QP ; 
 unsigned long long IB_USER_VERBS_EX_CMD_QUERY_DEVICE ; 
 scalar_t__ MLX5_CAP_DEV_MEM (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  MLX5_IB_UVERBS_ABI_VERSION ; 
 int /*<<< orphan*/  RDMA_DRIVER_MLX5 ; 
 int /*<<< orphan*/  disable_local_lb_mc ; 
 int /*<<< orphan*/  disable_local_lb_uc ; 
 int /*<<< orphan*/  get_dev_fw_str ; 
 int /*<<< orphan*/  imaicl ; 
 int init_node_data (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  ipoib_enhanced_offloads ; 
 int /*<<< orphan*/  memic ; 
 scalar_t__ mlx5_core_is_pf (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_get_umr_fence (scalar_t__) ; 
 int /*<<< orphan*/  mlx5_ib_add_gid ; 
 int /*<<< orphan*/  mlx5_ib_alloc_dm ; 
 int /*<<< orphan*/  mlx5_ib_alloc_mr ; 
 int /*<<< orphan*/  mlx5_ib_alloc_mw ; 
 int /*<<< orphan*/  mlx5_ib_alloc_pd ; 
 int /*<<< orphan*/  mlx5_ib_alloc_rdma_netdev ; 
 int /*<<< orphan*/  mlx5_ib_alloc_ucontext ; 
 int /*<<< orphan*/  mlx5_ib_alloc_xrcd ; 
 int /*<<< orphan*/  mlx5_ib_arm_cq ; 
 int /*<<< orphan*/  mlx5_ib_check_mr_status ; 
 int /*<<< orphan*/  mlx5_ib_create_ah ; 
 int /*<<< orphan*/  mlx5_ib_create_counters ; 
 int /*<<< orphan*/  mlx5_ib_create_cq ; 
 int /*<<< orphan*/  mlx5_ib_create_flow ; 
 int /*<<< orphan*/  mlx5_ib_create_flow_action_esp ; 
 int /*<<< orphan*/  mlx5_ib_create_qp ; 
 int /*<<< orphan*/  mlx5_ib_create_srq ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_dm ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_mw ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_pd ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_ucontext ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_xrcd ; 
 int /*<<< orphan*/  mlx5_ib_del_gid ; 
 int /*<<< orphan*/  mlx5_ib_dereg_mr ; 
 int /*<<< orphan*/  mlx5_ib_destroy_ah ; 
 int /*<<< orphan*/  mlx5_ib_destroy_counters ; 
 int /*<<< orphan*/  mlx5_ib_destroy_cq ; 
 int /*<<< orphan*/  mlx5_ib_destroy_flow ; 
 int /*<<< orphan*/  mlx5_ib_destroy_flow_action ; 
 int /*<<< orphan*/  mlx5_ib_destroy_qp ; 
 int /*<<< orphan*/  mlx5_ib_destroy_srq ; 
 int /*<<< orphan*/  mlx5_ib_disassociate_ucontext ; 
 int /*<<< orphan*/  mlx5_ib_drain_rq ; 
 int /*<<< orphan*/  mlx5_ib_drain_sq ; 
 int /*<<< orphan*/  mlx5_ib_get_dma_mr ; 
 int /*<<< orphan*/  mlx5_ib_get_vector_affinity ; 
 int /*<<< orphan*/  mlx5_ib_get_vf_config ; 
 int /*<<< orphan*/  mlx5_ib_get_vf_stats ; 
 int /*<<< orphan*/  mlx5_ib_map_mr_sg ; 
 int /*<<< orphan*/  mlx5_ib_mcg_attach ; 
 int /*<<< orphan*/  mlx5_ib_mcg_detach ; 
 int /*<<< orphan*/  mlx5_ib_mmap ; 
 int /*<<< orphan*/  mlx5_ib_modify_cq ; 
 int /*<<< orphan*/  mlx5_ib_modify_device ; 
 int /*<<< orphan*/  mlx5_ib_modify_flow_action_esp ; 
 int /*<<< orphan*/  mlx5_ib_modify_port ; 
 int /*<<< orphan*/  mlx5_ib_modify_qp ; 
 int /*<<< orphan*/  mlx5_ib_modify_srq ; 
 int /*<<< orphan*/  mlx5_ib_poll_cq ; 
 int /*<<< orphan*/  mlx5_ib_port_link_layer ; 
 int /*<<< orphan*/  mlx5_ib_post_recv ; 
 int /*<<< orphan*/  mlx5_ib_post_send ; 
 int /*<<< orphan*/  mlx5_ib_post_srq_recv ; 
 int /*<<< orphan*/  mlx5_ib_process_mad ; 
 int /*<<< orphan*/  mlx5_ib_query_ah ; 
 int /*<<< orphan*/  mlx5_ib_query_device ; 
 int /*<<< orphan*/  mlx5_ib_query_gid ; 
 int /*<<< orphan*/  mlx5_ib_query_pkey ; 
 int /*<<< orphan*/  mlx5_ib_query_qp ; 
 int /*<<< orphan*/  mlx5_ib_query_srq ; 
 int /*<<< orphan*/  mlx5_ib_read_counters ; 
 int /*<<< orphan*/  mlx5_ib_reg_dm_mr ; 
 int /*<<< orphan*/  mlx5_ib_reg_user_mr ; 
 int /*<<< orphan*/  mlx5_ib_rereg_user_mr ; 
 int /*<<< orphan*/  mlx5_ib_resize_cq ; 
 int /*<<< orphan*/  mlx5_ib_set_vf_guid ; 
 int /*<<< orphan*/  mlx5_ib_set_vf_link_state ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_type ; 
 int /*<<< orphan*/  umr_fence ; 
 int /*<<< orphan*/  xrc ; 

int mlx5_ib_stage_caps_init(struct mlx5_ib_dev *dev)
{
	struct mlx5_core_dev *mdev = dev->mdev;
	int err;

	dev->ib_dev.uverbs_abi_ver	= MLX5_IB_UVERBS_ABI_VERSION;
	dev->ib_dev.uverbs_cmd_mask	=
		(1ull << IB_USER_VERBS_CMD_GET_CONTEXT)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_DEVICE)	|
		(1ull << IB_USER_VERBS_CMD_QUERY_PORT)		|
		(1ull << IB_USER_VERBS_CMD_ALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_DEALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_AH)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_AH)		|
		(1ull << IB_USER_VERBS_CMD_REG_MR)		|
		(1ull << IB_USER_VERBS_CMD_REREG_MR)		|
		(1ull << IB_USER_VERBS_CMD_DEREG_MR)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL)	|
		(1ull << IB_USER_VERBS_CMD_CREATE_CQ)		|
		(1ull << IB_USER_VERBS_CMD_RESIZE_CQ)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_CQ)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_QP)		|
		(1ull << IB_USER_VERBS_CMD_MODIFY_QP)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_QP)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_QP)		|
		(1ull << IB_USER_VERBS_CMD_ATTACH_MCAST)	|
		(1ull << IB_USER_VERBS_CMD_DETACH_MCAST)	|
		(1ull << IB_USER_VERBS_CMD_CREATE_SRQ)		|
		(1ull << IB_USER_VERBS_CMD_MODIFY_SRQ)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_SRQ)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_SRQ)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_XSRQ)		|
		(1ull << IB_USER_VERBS_CMD_OPEN_QP);
	dev->ib_dev.uverbs_ex_cmd_mask =
		(1ull << IB_USER_VERBS_EX_CMD_QUERY_DEVICE)	|
		(1ull << IB_USER_VERBS_EX_CMD_CREATE_CQ)	|
		(1ull << IB_USER_VERBS_EX_CMD_CREATE_QP)	|
		(1ull << IB_USER_VERBS_EX_CMD_MODIFY_QP)	|
		(1ull << IB_USER_VERBS_EX_CMD_MODIFY_CQ);

	dev->ib_dev.query_device	= mlx5_ib_query_device;
	dev->ib_dev.get_link_layer	= mlx5_ib_port_link_layer;
	dev->ib_dev.query_gid		= mlx5_ib_query_gid;
	dev->ib_dev.add_gid		= mlx5_ib_add_gid;
	dev->ib_dev.del_gid		= mlx5_ib_del_gid;
	dev->ib_dev.query_pkey		= mlx5_ib_query_pkey;
	dev->ib_dev.modify_device	= mlx5_ib_modify_device;
	dev->ib_dev.modify_port		= mlx5_ib_modify_port;
	dev->ib_dev.alloc_ucontext	= mlx5_ib_alloc_ucontext;
	dev->ib_dev.dealloc_ucontext	= mlx5_ib_dealloc_ucontext;
	dev->ib_dev.mmap		= mlx5_ib_mmap;
	dev->ib_dev.alloc_pd		= mlx5_ib_alloc_pd;
	dev->ib_dev.dealloc_pd		= mlx5_ib_dealloc_pd;
	dev->ib_dev.create_ah		= mlx5_ib_create_ah;
	dev->ib_dev.query_ah		= mlx5_ib_query_ah;
	dev->ib_dev.destroy_ah		= mlx5_ib_destroy_ah;
	dev->ib_dev.create_srq		= mlx5_ib_create_srq;
	dev->ib_dev.modify_srq		= mlx5_ib_modify_srq;
	dev->ib_dev.query_srq		= mlx5_ib_query_srq;
	dev->ib_dev.destroy_srq		= mlx5_ib_destroy_srq;
	dev->ib_dev.post_srq_recv	= mlx5_ib_post_srq_recv;
	dev->ib_dev.create_qp		= mlx5_ib_create_qp;
	dev->ib_dev.modify_qp		= mlx5_ib_modify_qp;
	dev->ib_dev.query_qp		= mlx5_ib_query_qp;
	dev->ib_dev.destroy_qp		= mlx5_ib_destroy_qp;
	dev->ib_dev.drain_sq		= mlx5_ib_drain_sq;
	dev->ib_dev.drain_rq		= mlx5_ib_drain_rq;
	dev->ib_dev.post_send		= mlx5_ib_post_send;
	dev->ib_dev.post_recv		= mlx5_ib_post_recv;
	dev->ib_dev.create_cq		= mlx5_ib_create_cq;
	dev->ib_dev.modify_cq		= mlx5_ib_modify_cq;
	dev->ib_dev.resize_cq		= mlx5_ib_resize_cq;
	dev->ib_dev.destroy_cq		= mlx5_ib_destroy_cq;
	dev->ib_dev.poll_cq		= mlx5_ib_poll_cq;
	dev->ib_dev.req_notify_cq	= mlx5_ib_arm_cq;
	dev->ib_dev.get_dma_mr		= mlx5_ib_get_dma_mr;
	dev->ib_dev.reg_user_mr		= mlx5_ib_reg_user_mr;
	dev->ib_dev.rereg_user_mr	= mlx5_ib_rereg_user_mr;
	dev->ib_dev.dereg_mr		= mlx5_ib_dereg_mr;
	dev->ib_dev.attach_mcast	= mlx5_ib_mcg_attach;
	dev->ib_dev.detach_mcast	= mlx5_ib_mcg_detach;
	dev->ib_dev.process_mad		= mlx5_ib_process_mad;
	dev->ib_dev.alloc_mr		= mlx5_ib_alloc_mr;
	dev->ib_dev.map_mr_sg		= mlx5_ib_map_mr_sg;
	dev->ib_dev.check_mr_status	= mlx5_ib_check_mr_status;
	dev->ib_dev.get_dev_fw_str      = get_dev_fw_str;
	dev->ib_dev.get_vector_affinity	= mlx5_ib_get_vector_affinity;
	if (MLX5_CAP_GEN(mdev, ipoib_enhanced_offloads))
		dev->ib_dev.alloc_rdma_netdev	= mlx5_ib_alloc_rdma_netdev;

	if (mlx5_core_is_pf(mdev)) {
		dev->ib_dev.get_vf_config	= mlx5_ib_get_vf_config;
		dev->ib_dev.set_vf_link_state	= mlx5_ib_set_vf_link_state;
		dev->ib_dev.get_vf_stats	= mlx5_ib_get_vf_stats;
		dev->ib_dev.set_vf_guid		= mlx5_ib_set_vf_guid;
	}

	dev->ib_dev.disassociate_ucontext = mlx5_ib_disassociate_ucontext;

	dev->umr_fence = mlx5_get_umr_fence(MLX5_CAP_GEN(mdev, umr_fence));

	if (MLX5_CAP_GEN(mdev, imaicl)) {
		dev->ib_dev.alloc_mw		= mlx5_ib_alloc_mw;
		dev->ib_dev.dealloc_mw		= mlx5_ib_dealloc_mw;
		dev->ib_dev.uverbs_cmd_mask |=
			(1ull << IB_USER_VERBS_CMD_ALLOC_MW)	|
			(1ull << IB_USER_VERBS_CMD_DEALLOC_MW);
	}

	if (MLX5_CAP_GEN(mdev, xrc)) {
		dev->ib_dev.alloc_xrcd = mlx5_ib_alloc_xrcd;
		dev->ib_dev.dealloc_xrcd = mlx5_ib_dealloc_xrcd;
		dev->ib_dev.uverbs_cmd_mask |=
			(1ull << IB_USER_VERBS_CMD_OPEN_XRCD) |
			(1ull << IB_USER_VERBS_CMD_CLOSE_XRCD);
	}

	if (MLX5_CAP_DEV_MEM(mdev, memic)) {
		dev->ib_dev.alloc_dm = mlx5_ib_alloc_dm;
		dev->ib_dev.dealloc_dm = mlx5_ib_dealloc_dm;
		dev->ib_dev.reg_dm_mr = mlx5_ib_reg_dm_mr;
	}

	dev->ib_dev.create_flow	= mlx5_ib_create_flow;
	dev->ib_dev.destroy_flow = mlx5_ib_destroy_flow;
	dev->ib_dev.uverbs_ex_cmd_mask |=
			(1ull << IB_USER_VERBS_EX_CMD_CREATE_FLOW) |
			(1ull << IB_USER_VERBS_EX_CMD_DESTROY_FLOW);
	dev->ib_dev.create_flow_action_esp = mlx5_ib_create_flow_action_esp;
	dev->ib_dev.destroy_flow_action = mlx5_ib_destroy_flow_action;
	dev->ib_dev.modify_flow_action_esp = mlx5_ib_modify_flow_action_esp;
	dev->ib_dev.driver_id = RDMA_DRIVER_MLX5;
	dev->ib_dev.create_counters = mlx5_ib_create_counters;
	dev->ib_dev.destroy_counters = mlx5_ib_destroy_counters;
	dev->ib_dev.read_counters = mlx5_ib_read_counters;

	err = init_node_data(dev);
	if (err)
		return err;

	if ((MLX5_CAP_GEN(dev->mdev, port_type) == MLX5_CAP_PORT_TYPE_ETH) &&
	    (MLX5_CAP_GEN(dev->mdev, disable_local_lb_uc) ||
	     MLX5_CAP_GEN(dev->mdev, disable_local_lb_mc)))
		mutex_init(&dev->lb_mutex);

	return 0;
}