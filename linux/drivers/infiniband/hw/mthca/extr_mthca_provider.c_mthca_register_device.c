#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {unsigned long long uverbs_cmd_mask; int num_comp_vectors; TYPE_2__ dev; int /*<<< orphan*/  phys_port_cnt; int /*<<< orphan*/  node_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_ports; } ;
struct mthca_dev {int mthca_flags; TYPE_4__ ib_dev; int /*<<< orphan*/  cap_mask_mutex; TYPE_3__* pdev; TYPE_1__ limits; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long long IB_USER_VERBS_CMD_ALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_ATTACH_MCAST ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_QP ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_DEALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_DEREG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_DETACH_MCAST ; 
 unsigned long long IB_USER_VERBS_CMD_GET_CONTEXT ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_DEVICE ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_PORT ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_REG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_RESIZE_CQ ; 
 int MTHCA_FLAG_FMR ; 
 int MTHCA_FLAG_SRQ ; 
 int /*<<< orphan*/  RDMA_NODE_IB_CA ; 
 int ib_register_device (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  ib_set_device_ops (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_attr_group ; 
 int /*<<< orphan*/  mthca_dev_arbel_fmr_ops ; 
 int /*<<< orphan*/  mthca_dev_arbel_ops ; 
 int /*<<< orphan*/  mthca_dev_arbel_srq_ops ; 
 int /*<<< orphan*/  mthca_dev_ops ; 
 int /*<<< orphan*/  mthca_dev_tavor_fmr_ops ; 
 int /*<<< orphan*/  mthca_dev_tavor_ops ; 
 int /*<<< orphan*/  mthca_dev_tavor_srq_ops ; 
 int mthca_init_node_data (struct mthca_dev*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_start_catas_poll (struct mthca_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_set_device_sysfs_group (TYPE_4__*,int /*<<< orphan*/ *) ; 

int mthca_register_device(struct mthca_dev *dev)
{
	int ret;

	ret = mthca_init_node_data(dev);
	if (ret)
		return ret;

	dev->ib_dev.uverbs_cmd_mask	 =
		(1ull << IB_USER_VERBS_CMD_GET_CONTEXT)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_DEVICE)	|
		(1ull << IB_USER_VERBS_CMD_QUERY_PORT)		|
		(1ull << IB_USER_VERBS_CMD_ALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_DEALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_REG_MR)		|
		(1ull << IB_USER_VERBS_CMD_DEREG_MR)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL)	|
		(1ull << IB_USER_VERBS_CMD_CREATE_CQ)		|
		(1ull << IB_USER_VERBS_CMD_RESIZE_CQ)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_CQ)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_QP)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_QP)		|
		(1ull << IB_USER_VERBS_CMD_MODIFY_QP)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_QP)		|
		(1ull << IB_USER_VERBS_CMD_ATTACH_MCAST)	|
		(1ull << IB_USER_VERBS_CMD_DETACH_MCAST);
	dev->ib_dev.node_type            = RDMA_NODE_IB_CA;
	dev->ib_dev.phys_port_cnt        = dev->limits.num_ports;
	dev->ib_dev.num_comp_vectors     = 1;
	dev->ib_dev.dev.parent           = &dev->pdev->dev;

	if (dev->mthca_flags & MTHCA_FLAG_SRQ) {
		dev->ib_dev.uverbs_cmd_mask	|=
			(1ull << IB_USER_VERBS_CMD_CREATE_SRQ)		|
			(1ull << IB_USER_VERBS_CMD_MODIFY_SRQ)		|
			(1ull << IB_USER_VERBS_CMD_QUERY_SRQ)		|
			(1ull << IB_USER_VERBS_CMD_DESTROY_SRQ);

		if (mthca_is_memfree(dev))
			ib_set_device_ops(&dev->ib_dev,
					  &mthca_dev_arbel_srq_ops);
		else
			ib_set_device_ops(&dev->ib_dev,
					  &mthca_dev_tavor_srq_ops);
	}

	if (dev->mthca_flags & MTHCA_FLAG_FMR) {
		if (mthca_is_memfree(dev))
			ib_set_device_ops(&dev->ib_dev,
					  &mthca_dev_arbel_fmr_ops);
		else
			ib_set_device_ops(&dev->ib_dev,
					  &mthca_dev_tavor_fmr_ops);
	}

	ib_set_device_ops(&dev->ib_dev, &mthca_dev_ops);

	if (mthca_is_memfree(dev))
		ib_set_device_ops(&dev->ib_dev, &mthca_dev_arbel_ops);
	else
		ib_set_device_ops(&dev->ib_dev, &mthca_dev_tavor_ops);

	mutex_init(&dev->cap_mask_mutex);

	rdma_set_device_sysfs_group(&dev->ib_dev, &mthca_attr_group);
	ret = ib_register_device(&dev->ib_dev, "mthca%d");
	if (ret)
		return ret;

	mthca_start_catas_poll(dev);

	return 0;
}