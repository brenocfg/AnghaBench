#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pvrdma_srq {int dummy; } ;
struct pvrdma_qp {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {int num_comp_vectors; unsigned long long uverbs_cmd_mask; TYPE_6__ dev; int /*<<< orphan*/  driver_id; int /*<<< orphan*/  destroy_srq; int /*<<< orphan*/  query_srq; int /*<<< orphan*/  modify_srq; int /*<<< orphan*/  create_srq; int /*<<< orphan*/  get_dev_fw_str; int /*<<< orphan*/  get_link_layer; int /*<<< orphan*/  get_port_immutable; int /*<<< orphan*/  get_netdev; int /*<<< orphan*/  del_gid; int /*<<< orphan*/  add_gid; int /*<<< orphan*/  map_mr_sg; int /*<<< orphan*/  alloc_mr; int /*<<< orphan*/  dereg_mr; int /*<<< orphan*/  reg_user_mr; int /*<<< orphan*/  get_dma_mr; int /*<<< orphan*/  req_notify_cq; int /*<<< orphan*/  poll_cq; int /*<<< orphan*/  destroy_cq; int /*<<< orphan*/  create_cq; int /*<<< orphan*/  post_recv; int /*<<< orphan*/  post_send; int /*<<< orphan*/  destroy_qp; int /*<<< orphan*/  query_qp; int /*<<< orphan*/  modify_qp; int /*<<< orphan*/  create_qp; int /*<<< orphan*/  destroy_ah; int /*<<< orphan*/  create_ah; int /*<<< orphan*/  dealloc_pd; int /*<<< orphan*/  alloc_pd; int /*<<< orphan*/  mmap; int /*<<< orphan*/  dealloc_ucontext; int /*<<< orphan*/  alloc_ucontext; int /*<<< orphan*/  modify_port; int /*<<< orphan*/  query_pkey; int /*<<< orphan*/  query_gid; int /*<<< orphan*/  query_port; int /*<<< orphan*/  query_device; int /*<<< orphan*/  phys_port_cnt; int /*<<< orphan*/  node_type; int /*<<< orphan*/  uverbs_abi_ver; int /*<<< orphan*/  owner; int /*<<< orphan*/  node_guid; int /*<<< orphan*/  name; } ;
struct pvrdma_dev {int ib_active; void* cq_tbl; void* qp_tbl; void* srq_tbl; TYPE_4__ ib_dev; int /*<<< orphan*/  srq_tbl_lock; TYPE_3__* dsr; int /*<<< orphan*/  qp_tbl_lock; int /*<<< orphan*/  cq_tbl_lock; int /*<<< orphan*/  desc_lock; int /*<<< orphan*/  port_mutex; TYPE_1__* pdev; scalar_t__ flags; int /*<<< orphan*/  sys_image_guid; } ;
struct pvrdma_cq {int dummy; } ;
struct TYPE_8__ {scalar_t__ max_srq; scalar_t__ max_qp; scalar_t__ max_cq; int /*<<< orphan*/  phys_port_cnt; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  node_guid; } ;
struct TYPE_9__ {TYPE_2__ caps; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_DEVICE_NAME_MAX ; 
 unsigned long long IB_USER_VERBS_CMD_ALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_AH ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_QP ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_DEALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_DEREG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_AH ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_GET_CONTEXT ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_POLL_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_POST_RECV ; 
 unsigned long long IB_USER_VERBS_CMD_POST_SEND ; 
 unsigned long long IB_USER_VERBS_CMD_POST_SRQ_RECV ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_DEVICE ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_PORT ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_REG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_REQ_NOTIFY_CQ ; 
 int /*<<< orphan*/  PVRDMA_UVERBS_ABI_VERSION ; 
 int /*<<< orphan*/  RDMA_DRIVER_VMW_PVRDMA ; 
 int /*<<< orphan*/  RDMA_NODE_IB_CA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int device_create_file (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int ib_register_device (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (TYPE_4__*) ; 
 void* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvrdma_add_gid ; 
 int /*<<< orphan*/  pvrdma_alloc_mr ; 
 int /*<<< orphan*/  pvrdma_alloc_pd ; 
 int /*<<< orphan*/  pvrdma_alloc_ucontext ; 
 int /*<<< orphan*/ * pvrdma_class_attributes ; 
 int /*<<< orphan*/  pvrdma_create_ah ; 
 int /*<<< orphan*/  pvrdma_create_cq ; 
 int /*<<< orphan*/  pvrdma_create_qp ; 
 int /*<<< orphan*/  pvrdma_create_srq ; 
 int /*<<< orphan*/  pvrdma_dealloc_pd ; 
 int /*<<< orphan*/  pvrdma_dealloc_ucontext ; 
 int /*<<< orphan*/  pvrdma_del_gid ; 
 int /*<<< orphan*/  pvrdma_dereg_mr ; 
 int /*<<< orphan*/  pvrdma_destroy_ah ; 
 int /*<<< orphan*/  pvrdma_destroy_cq ; 
 int /*<<< orphan*/  pvrdma_destroy_qp ; 
 int /*<<< orphan*/  pvrdma_destroy_srq ; 
 int /*<<< orphan*/  pvrdma_get_dma_mr ; 
 int /*<<< orphan*/  pvrdma_get_fw_ver_str ; 
 int /*<<< orphan*/  pvrdma_get_netdev ; 
 int /*<<< orphan*/  pvrdma_map_mr_sg ; 
 int /*<<< orphan*/  pvrdma_mmap ; 
 int /*<<< orphan*/  pvrdma_modify_port ; 
 int /*<<< orphan*/  pvrdma_modify_qp ; 
 int /*<<< orphan*/  pvrdma_modify_srq ; 
 int /*<<< orphan*/  pvrdma_poll_cq ; 
 int /*<<< orphan*/  pvrdma_port_immutable ; 
 int /*<<< orphan*/  pvrdma_port_link_layer ; 
 int /*<<< orphan*/  pvrdma_post_recv ; 
 int /*<<< orphan*/  pvrdma_post_send ; 
 int /*<<< orphan*/  pvrdma_query_device ; 
 int /*<<< orphan*/  pvrdma_query_gid ; 
 int /*<<< orphan*/  pvrdma_query_pkey ; 
 int /*<<< orphan*/  pvrdma_query_port ; 
 int /*<<< orphan*/  pvrdma_query_qp ; 
 int /*<<< orphan*/  pvrdma_query_srq ; 
 int /*<<< orphan*/  pvrdma_reg_user_mr ; 
 int /*<<< orphan*/  pvrdma_req_notify_cq ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvrdma_register_device(struct pvrdma_dev *dev)
{
	int ret = -1;
	int i = 0;

	strlcpy(dev->ib_dev.name, "vmw_pvrdma%d", IB_DEVICE_NAME_MAX);
	dev->ib_dev.node_guid = dev->dsr->caps.node_guid;
	dev->sys_image_guid = dev->dsr->caps.sys_image_guid;
	dev->flags = 0;
	dev->ib_dev.owner = THIS_MODULE;
	dev->ib_dev.num_comp_vectors = 1;
	dev->ib_dev.dev.parent = &dev->pdev->dev;
	dev->ib_dev.uverbs_abi_ver = PVRDMA_UVERBS_ABI_VERSION;
	dev->ib_dev.uverbs_cmd_mask =
		(1ull << IB_USER_VERBS_CMD_GET_CONTEXT)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_DEVICE)	|
		(1ull << IB_USER_VERBS_CMD_QUERY_PORT)		|
		(1ull << IB_USER_VERBS_CMD_ALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_DEALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_REG_MR)		|
		(1ull << IB_USER_VERBS_CMD_DEREG_MR)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL)	|
		(1ull << IB_USER_VERBS_CMD_CREATE_CQ)		|
		(1ull << IB_USER_VERBS_CMD_POLL_CQ)		|
		(1ull << IB_USER_VERBS_CMD_REQ_NOTIFY_CQ)	|
		(1ull << IB_USER_VERBS_CMD_DESTROY_CQ)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_QP)		|
		(1ull << IB_USER_VERBS_CMD_MODIFY_QP)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_QP)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_QP)		|
		(1ull << IB_USER_VERBS_CMD_POST_SEND)		|
		(1ull << IB_USER_VERBS_CMD_POST_RECV)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_AH)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_AH);

	dev->ib_dev.node_type = RDMA_NODE_IB_CA;
	dev->ib_dev.phys_port_cnt = dev->dsr->caps.phys_port_cnt;

	dev->ib_dev.query_device = pvrdma_query_device;
	dev->ib_dev.query_port = pvrdma_query_port;
	dev->ib_dev.query_gid = pvrdma_query_gid;
	dev->ib_dev.query_pkey = pvrdma_query_pkey;
	dev->ib_dev.modify_port	= pvrdma_modify_port;
	dev->ib_dev.alloc_ucontext = pvrdma_alloc_ucontext;
	dev->ib_dev.dealloc_ucontext = pvrdma_dealloc_ucontext;
	dev->ib_dev.mmap = pvrdma_mmap;
	dev->ib_dev.alloc_pd = pvrdma_alloc_pd;
	dev->ib_dev.dealloc_pd = pvrdma_dealloc_pd;
	dev->ib_dev.create_ah = pvrdma_create_ah;
	dev->ib_dev.destroy_ah = pvrdma_destroy_ah;
	dev->ib_dev.create_qp = pvrdma_create_qp;
	dev->ib_dev.modify_qp = pvrdma_modify_qp;
	dev->ib_dev.query_qp = pvrdma_query_qp;
	dev->ib_dev.destroy_qp = pvrdma_destroy_qp;
	dev->ib_dev.post_send = pvrdma_post_send;
	dev->ib_dev.post_recv = pvrdma_post_recv;
	dev->ib_dev.create_cq = pvrdma_create_cq;
	dev->ib_dev.destroy_cq = pvrdma_destroy_cq;
	dev->ib_dev.poll_cq = pvrdma_poll_cq;
	dev->ib_dev.req_notify_cq = pvrdma_req_notify_cq;
	dev->ib_dev.get_dma_mr = pvrdma_get_dma_mr;
	dev->ib_dev.reg_user_mr	= pvrdma_reg_user_mr;
	dev->ib_dev.dereg_mr = pvrdma_dereg_mr;
	dev->ib_dev.alloc_mr = pvrdma_alloc_mr;
	dev->ib_dev.map_mr_sg = pvrdma_map_mr_sg;
	dev->ib_dev.add_gid = pvrdma_add_gid;
	dev->ib_dev.del_gid = pvrdma_del_gid;
	dev->ib_dev.get_netdev = pvrdma_get_netdev;
	dev->ib_dev.get_port_immutable = pvrdma_port_immutable;
	dev->ib_dev.get_link_layer = pvrdma_port_link_layer;
	dev->ib_dev.get_dev_fw_str = pvrdma_get_fw_ver_str;

	mutex_init(&dev->port_mutex);
	spin_lock_init(&dev->desc_lock);

	dev->cq_tbl = kcalloc(dev->dsr->caps.max_cq, sizeof(struct pvrdma_cq *),
			      GFP_KERNEL);
	if (!dev->cq_tbl)
		return ret;
	spin_lock_init(&dev->cq_tbl_lock);

	dev->qp_tbl = kcalloc(dev->dsr->caps.max_qp, sizeof(struct pvrdma_qp *),
			      GFP_KERNEL);
	if (!dev->qp_tbl)
		goto err_cq_free;
	spin_lock_init(&dev->qp_tbl_lock);

	/* Check if SRQ is supported by backend */
	if (dev->dsr->caps.max_srq) {
		dev->ib_dev.uverbs_cmd_mask |=
			(1ull << IB_USER_VERBS_CMD_CREATE_SRQ)	|
			(1ull << IB_USER_VERBS_CMD_MODIFY_SRQ)	|
			(1ull << IB_USER_VERBS_CMD_QUERY_SRQ)	|
			(1ull << IB_USER_VERBS_CMD_DESTROY_SRQ)	|
			(1ull << IB_USER_VERBS_CMD_POST_SRQ_RECV);

		dev->ib_dev.create_srq = pvrdma_create_srq;
		dev->ib_dev.modify_srq = pvrdma_modify_srq;
		dev->ib_dev.query_srq = pvrdma_query_srq;
		dev->ib_dev.destroy_srq = pvrdma_destroy_srq;

		dev->srq_tbl = kcalloc(dev->dsr->caps.max_srq,
				       sizeof(struct pvrdma_srq *),
				       GFP_KERNEL);
		if (!dev->srq_tbl)
			goto err_qp_free;
	}
	dev->ib_dev.driver_id = RDMA_DRIVER_VMW_PVRDMA;
	spin_lock_init(&dev->srq_tbl_lock);

	ret = ib_register_device(&dev->ib_dev, NULL);
	if (ret)
		goto err_srq_free;

	for (i = 0; i < ARRAY_SIZE(pvrdma_class_attributes); ++i) {
		ret = device_create_file(&dev->ib_dev.dev,
					 pvrdma_class_attributes[i]);
		if (ret)
			goto err_class;
	}

	dev->ib_active = true;

	return 0;

err_class:
	ib_unregister_device(&dev->ib_dev);
err_srq_free:
	kfree(dev->srq_tbl);
err_qp_free:
	kfree(dev->qp_tbl);
err_cq_free:
	kfree(dev->cq_tbl);

	return ret;
}