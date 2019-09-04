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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {unsigned long long uverbs_cmd_mask; int phys_port_cnt; int /*<<< orphan*/  get_vector_affinity; int /*<<< orphan*/  post_recv; int /*<<< orphan*/  post_send; int /*<<< orphan*/  req_notify_cq; int /*<<< orphan*/  poll_cq; int /*<<< orphan*/  get_dev_fw_str; int /*<<< orphan*/  get_port_immutable; TYPE_3__* iwcm; int /*<<< orphan*/  map_mr_sg; int /*<<< orphan*/  alloc_mr; int /*<<< orphan*/  drain_rq; int /*<<< orphan*/  drain_sq; int /*<<< orphan*/  query_device; int /*<<< orphan*/  get_hw_stats; int /*<<< orphan*/  alloc_hw_stats; int /*<<< orphan*/  dereg_mr; int /*<<< orphan*/  reg_user_mr; int /*<<< orphan*/  get_dma_mr; int /*<<< orphan*/  destroy_cq; int /*<<< orphan*/  create_cq; int /*<<< orphan*/  destroy_qp; int /*<<< orphan*/  query_qp; int /*<<< orphan*/  modify_qp; int /*<<< orphan*/  create_qp; int /*<<< orphan*/  dealloc_pd; int /*<<< orphan*/  alloc_pd; int /*<<< orphan*/  mmap; int /*<<< orphan*/  dealloc_ucontext; int /*<<< orphan*/  alloc_ucontext; int /*<<< orphan*/  query_gid; int /*<<< orphan*/  query_pkey; int /*<<< orphan*/  query_port; TYPE_2__ dev; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  node_guid; int /*<<< orphan*/  node_type; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct i40iw_ib_device {TYPE_4__ ibdev; struct i40iw_device* iwdev; } ;
struct TYPE_5__ {scalar_t__ dev_context; } ;
struct i40iw_device {int /*<<< orphan*/  ceqs_count; struct i40iw_ib_device* iwibdev; TYPE_1__ hw; struct net_device* netdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  ifname; int /*<<< orphan*/  destroy_listen; int /*<<< orphan*/  create_listen; int /*<<< orphan*/  reject; int /*<<< orphan*/  accept; int /*<<< orphan*/  connect; int /*<<< orphan*/  get_qp; int /*<<< orphan*/  rem_ref; int /*<<< orphan*/  add_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_DEVICE_NAME_MAX ; 
 unsigned long long IB_USER_VERBS_CMD_ALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_AH ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_QP ; 
 unsigned long long IB_USER_VERBS_CMD_DEALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_DEREG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_AH ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_GET_CONTEXT ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_POLL_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_POST_RECV ; 
 unsigned long long IB_USER_VERBS_CMD_POST_SEND ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_DEVICE ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_PORT ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_REG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_REQ_NOTIFY_CQ ; 
 int /*<<< orphan*/  RDMA_NODE_RNIC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_accept ; 
 int /*<<< orphan*/  i40iw_add_ref ; 
 int /*<<< orphan*/  i40iw_alloc_hw_stats ; 
 int /*<<< orphan*/  i40iw_alloc_mr ; 
 int /*<<< orphan*/  i40iw_alloc_pd ; 
 int /*<<< orphan*/  i40iw_alloc_ucontext ; 
 int /*<<< orphan*/  i40iw_connect ; 
 int /*<<< orphan*/  i40iw_create_cq ; 
 int /*<<< orphan*/  i40iw_create_listen ; 
 int /*<<< orphan*/  i40iw_create_qp ; 
 int /*<<< orphan*/  i40iw_dealloc_pd ; 
 int /*<<< orphan*/  i40iw_dealloc_ucontext ; 
 int /*<<< orphan*/  i40iw_dereg_mr ; 
 int /*<<< orphan*/  i40iw_destroy_cq ; 
 int /*<<< orphan*/  i40iw_destroy_listen ; 
 int /*<<< orphan*/  i40iw_destroy_qp ; 
 int /*<<< orphan*/  i40iw_drain_rq ; 
 int /*<<< orphan*/  i40iw_drain_sq ; 
 int /*<<< orphan*/  i40iw_get_dev_fw_str ; 
 int /*<<< orphan*/  i40iw_get_dma_mr ; 
 int /*<<< orphan*/  i40iw_get_hw_stats ; 
 int /*<<< orphan*/  i40iw_get_qp ; 
 int /*<<< orphan*/  i40iw_get_vector_affinity ; 
 int /*<<< orphan*/  i40iw_map_mr_sg ; 
 int /*<<< orphan*/  i40iw_mmap ; 
 int /*<<< orphan*/  i40iw_modify_qp ; 
 int /*<<< orphan*/  i40iw_poll_cq ; 
 int /*<<< orphan*/  i40iw_port_immutable ; 
 int /*<<< orphan*/  i40iw_post_recv ; 
 int /*<<< orphan*/  i40iw_post_send ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  i40iw_query_device ; 
 int /*<<< orphan*/  i40iw_query_gid ; 
 int /*<<< orphan*/  i40iw_query_pkey ; 
 int /*<<< orphan*/  i40iw_query_port ; 
 int /*<<< orphan*/  i40iw_query_qp ; 
 int /*<<< orphan*/  i40iw_reg_user_mr ; 
 int /*<<< orphan*/  i40iw_reject ; 
 int /*<<< orphan*/  i40iw_rem_ref ; 
 int /*<<< orphan*/  i40iw_req_notify_cq ; 
 scalar_t__ ib_alloc_device (int) ; 
 int /*<<< orphan*/  ib_dealloc_device (TYPE_4__*) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i40iw_ib_device *i40iw_init_rdma_device(struct i40iw_device *iwdev)
{
	struct i40iw_ib_device *iwibdev;
	struct net_device *netdev = iwdev->netdev;
	struct pci_dev *pcidev = (struct pci_dev *)iwdev->hw.dev_context;

	iwibdev = (struct i40iw_ib_device *)ib_alloc_device(sizeof(*iwibdev));
	if (!iwibdev) {
		i40iw_pr_err("iwdev == NULL\n");
		return NULL;
	}
	strlcpy(iwibdev->ibdev.name, "i40iw%d", IB_DEVICE_NAME_MAX);
	iwibdev->ibdev.owner = THIS_MODULE;
	iwdev->iwibdev = iwibdev;
	iwibdev->iwdev = iwdev;

	iwibdev->ibdev.node_type = RDMA_NODE_RNIC;
	ether_addr_copy((u8 *)&iwibdev->ibdev.node_guid, netdev->dev_addr);

	iwibdev->ibdev.uverbs_cmd_mask =
	    (1ull << IB_USER_VERBS_CMD_GET_CONTEXT) |
	    (1ull << IB_USER_VERBS_CMD_QUERY_DEVICE) |
	    (1ull << IB_USER_VERBS_CMD_QUERY_PORT) |
	    (1ull << IB_USER_VERBS_CMD_ALLOC_PD) |
	    (1ull << IB_USER_VERBS_CMD_DEALLOC_PD) |
	    (1ull << IB_USER_VERBS_CMD_REG_MR) |
	    (1ull << IB_USER_VERBS_CMD_DEREG_MR) |
	    (1ull << IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL) |
	    (1ull << IB_USER_VERBS_CMD_CREATE_CQ) |
	    (1ull << IB_USER_VERBS_CMD_DESTROY_CQ) |
	    (1ull << IB_USER_VERBS_CMD_REQ_NOTIFY_CQ) |
	    (1ull << IB_USER_VERBS_CMD_CREATE_QP) |
	    (1ull << IB_USER_VERBS_CMD_MODIFY_QP) |
	    (1ull << IB_USER_VERBS_CMD_QUERY_QP) |
	    (1ull << IB_USER_VERBS_CMD_POLL_CQ) |
	    (1ull << IB_USER_VERBS_CMD_CREATE_AH) |
	    (1ull << IB_USER_VERBS_CMD_DESTROY_AH) |
	    (1ull << IB_USER_VERBS_CMD_DESTROY_QP) |
	    (1ull << IB_USER_VERBS_CMD_POST_RECV) |
	    (1ull << IB_USER_VERBS_CMD_POST_SEND);
	iwibdev->ibdev.phys_port_cnt = 1;
	iwibdev->ibdev.num_comp_vectors = iwdev->ceqs_count;
	iwibdev->ibdev.dev.parent = &pcidev->dev;
	iwibdev->ibdev.query_port = i40iw_query_port;
	iwibdev->ibdev.query_pkey = i40iw_query_pkey;
	iwibdev->ibdev.query_gid = i40iw_query_gid;
	iwibdev->ibdev.alloc_ucontext = i40iw_alloc_ucontext;
	iwibdev->ibdev.dealloc_ucontext = i40iw_dealloc_ucontext;
	iwibdev->ibdev.mmap = i40iw_mmap;
	iwibdev->ibdev.alloc_pd = i40iw_alloc_pd;
	iwibdev->ibdev.dealloc_pd = i40iw_dealloc_pd;
	iwibdev->ibdev.create_qp = i40iw_create_qp;
	iwibdev->ibdev.modify_qp = i40iw_modify_qp;
	iwibdev->ibdev.query_qp = i40iw_query_qp;
	iwibdev->ibdev.destroy_qp = i40iw_destroy_qp;
	iwibdev->ibdev.create_cq = i40iw_create_cq;
	iwibdev->ibdev.destroy_cq = i40iw_destroy_cq;
	iwibdev->ibdev.get_dma_mr = i40iw_get_dma_mr;
	iwibdev->ibdev.reg_user_mr = i40iw_reg_user_mr;
	iwibdev->ibdev.dereg_mr = i40iw_dereg_mr;
	iwibdev->ibdev.alloc_hw_stats = i40iw_alloc_hw_stats;
	iwibdev->ibdev.get_hw_stats = i40iw_get_hw_stats;
	iwibdev->ibdev.query_device = i40iw_query_device;
	iwibdev->ibdev.drain_sq = i40iw_drain_sq;
	iwibdev->ibdev.drain_rq = i40iw_drain_rq;
	iwibdev->ibdev.alloc_mr = i40iw_alloc_mr;
	iwibdev->ibdev.map_mr_sg = i40iw_map_mr_sg;
	iwibdev->ibdev.iwcm = kzalloc(sizeof(*iwibdev->ibdev.iwcm), GFP_KERNEL);
	if (!iwibdev->ibdev.iwcm) {
		ib_dealloc_device(&iwibdev->ibdev);
		return NULL;
	}

	iwibdev->ibdev.iwcm->add_ref = i40iw_add_ref;
	iwibdev->ibdev.iwcm->rem_ref = i40iw_rem_ref;
	iwibdev->ibdev.iwcm->get_qp = i40iw_get_qp;
	iwibdev->ibdev.iwcm->connect = i40iw_connect;
	iwibdev->ibdev.iwcm->accept = i40iw_accept;
	iwibdev->ibdev.iwcm->reject = i40iw_reject;
	iwibdev->ibdev.iwcm->create_listen = i40iw_create_listen;
	iwibdev->ibdev.iwcm->destroy_listen = i40iw_destroy_listen;
	memcpy(iwibdev->ibdev.iwcm->ifname, netdev->name,
	       sizeof(iwibdev->ibdev.iwcm->ifname));
	iwibdev->ibdev.get_port_immutable   = i40iw_port_immutable;
	iwibdev->ibdev.get_dev_fw_str       = i40iw_get_dev_fw_str;
	iwibdev->ibdev.poll_cq = i40iw_poll_cq;
	iwibdev->ibdev.req_notify_cq = i40iw_req_notify_cq;
	iwibdev->ibdev.post_send = i40iw_post_send;
	iwibdev->ibdev.post_recv = i40iw_post_recv;
	iwibdev->ibdev.get_vector_affinity = i40iw_get_vector_affinity;

	return iwibdev;
}