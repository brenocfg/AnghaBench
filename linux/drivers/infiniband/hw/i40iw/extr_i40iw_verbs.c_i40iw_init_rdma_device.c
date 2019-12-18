#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {unsigned long long uverbs_cmd_mask; int phys_port_cnt; int /*<<< orphan*/  iw_ifname; TYPE_2__ dev; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  node_guid; int /*<<< orphan*/  node_type; } ;
struct i40iw_ib_device {TYPE_3__ ibdev; struct i40iw_device* iwdev; } ;
struct TYPE_4__ {scalar_t__ dev_context; } ;
struct i40iw_device {int /*<<< orphan*/  ceqs_count; struct i40iw_ib_device* iwibdev; TYPE_1__ hw; struct net_device* netdev; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_dev_ops ; 
 int /*<<< orphan*/  i40iw_ib_device ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 struct i40iw_ib_device* ib_alloc_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_set_device_ops (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibdev ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct i40iw_ib_device *i40iw_init_rdma_device(struct i40iw_device *iwdev)
{
	struct i40iw_ib_device *iwibdev;
	struct net_device *netdev = iwdev->netdev;
	struct pci_dev *pcidev = (struct pci_dev *)iwdev->hw.dev_context;

	iwibdev = ib_alloc_device(i40iw_ib_device, ibdev);
	if (!iwibdev) {
		i40iw_pr_err("iwdev == NULL\n");
		return NULL;
	}
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
	memcpy(iwibdev->ibdev.iw_ifname, netdev->name,
	       sizeof(iwibdev->ibdev.iw_ifname));
	ib_set_device_ops(&iwibdev->ibdev, &i40iw_dev_ops);

	return iwibdev;
}