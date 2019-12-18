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
typedef  int /*<<< orphan*/  u8 ;
struct ql3_adapter {int num_lbufq_entries; int num_large_buffers; int /*<<< orphan*/  shadow_reg_phy_addr; int /*<<< orphan*/ * shadow_reg_virt_addr; int /*<<< orphan*/  pdev; int /*<<< orphan*/  rsp_q_virt_addr; int /*<<< orphan*/  rsp_current; TYPE_1__* ndev; scalar_t__ req_consumer_index_phy_addr_low; scalar_t__ rsp_producer_index_phy_addr_low; int /*<<< orphan*/  req_consumer_index_phy_addr_high; int /*<<< orphan*/  rsp_producer_index_phy_addr_high; int /*<<< orphan*/ * preq_consumer_index; int /*<<< orphan*/ * prsp_producer_index; scalar_t__ lrg_buffer_len; scalar_t__ max_frame_size; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ETHERNET_CRC_SIZE ; 
 scalar_t__ JUMBO_MTU_SIZE ; 
 int JUMBO_NUM_LBUFQ_ENTRIES ; 
 scalar_t__ LS_64BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_64BITS (int /*<<< orphan*/ ) ; 
 scalar_t__ NORMAL_MTU_SIZE ; 
 int NUM_LBUFQ_ENTRIES ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int QL_ADDR_ELE_PER_BUFQ_ENTRY ; 
 scalar_t__ QL_HEADER_SPACE ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 scalar_t__ VLAN_ID_LEN ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ql_alloc_buffer_queues (struct ql3_adapter*) ; 
 scalar_t__ ql_alloc_large_buffers (struct ql3_adapter*) ; 
 scalar_t__ ql_alloc_net_req_rsp_queues (struct ql3_adapter*) ; 
 scalar_t__ ql_alloc_small_buffers (struct ql3_adapter*) ; 
 scalar_t__ ql_create_send_free_list (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_free_buffer_queues (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_free_net_req_rsp_queues (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_free_send_free_list (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_init_large_buffers (struct ql3_adapter*) ; 

__attribute__((used)) static int ql_alloc_mem_resources(struct ql3_adapter *qdev)
{
	if (qdev->ndev->mtu == NORMAL_MTU_SIZE) {
		qdev->num_lbufq_entries = NUM_LBUFQ_ENTRIES;
		qdev->lrg_buffer_len = NORMAL_MTU_SIZE;
	} else if (qdev->ndev->mtu == JUMBO_MTU_SIZE) {
		/*
		 * Bigger buffers, so less of them.
		 */
		qdev->num_lbufq_entries = JUMBO_NUM_LBUFQ_ENTRIES;
		qdev->lrg_buffer_len = JUMBO_MTU_SIZE;
	} else {
		netdev_err(qdev->ndev, "Invalid mtu size: %d.  Only %d and %d are accepted.\n",
			   qdev->ndev->mtu, NORMAL_MTU_SIZE, JUMBO_MTU_SIZE);
		return -ENOMEM;
	}
	qdev->num_large_buffers =
		qdev->num_lbufq_entries * QL_ADDR_ELE_PER_BUFQ_ENTRY;
	qdev->lrg_buffer_len += VLAN_ETH_HLEN + VLAN_ID_LEN + QL_HEADER_SPACE;
	qdev->max_frame_size =
		(qdev->lrg_buffer_len - QL_HEADER_SPACE) + ETHERNET_CRC_SIZE;

	/*
	 * First allocate a page of shared memory and use it for shadow
	 * locations of Network Request Queue Consumer Address Register and
	 * Network Completion Queue Producer Index Register
	 */
	qdev->shadow_reg_virt_addr =
		pci_alloc_consistent(qdev->pdev,
				     PAGE_SIZE, &qdev->shadow_reg_phy_addr);

	if (qdev->shadow_reg_virt_addr != NULL) {
		qdev->preq_consumer_index = qdev->shadow_reg_virt_addr;
		qdev->req_consumer_index_phy_addr_high =
			MS_64BITS(qdev->shadow_reg_phy_addr);
		qdev->req_consumer_index_phy_addr_low =
			LS_64BITS(qdev->shadow_reg_phy_addr);

		qdev->prsp_producer_index =
			(__le32 *) (((u8 *) qdev->preq_consumer_index) + 8);
		qdev->rsp_producer_index_phy_addr_high =
			qdev->req_consumer_index_phy_addr_high;
		qdev->rsp_producer_index_phy_addr_low =
			qdev->req_consumer_index_phy_addr_low + 8;
	} else {
		netdev_err(qdev->ndev, "shadowReg Alloc failed\n");
		return -ENOMEM;
	}

	if (ql_alloc_net_req_rsp_queues(qdev) != 0) {
		netdev_err(qdev->ndev, "ql_alloc_net_req_rsp_queues failed\n");
		goto err_req_rsp;
	}

	if (ql_alloc_buffer_queues(qdev) != 0) {
		netdev_err(qdev->ndev, "ql_alloc_buffer_queues failed\n");
		goto err_buffer_queues;
	}

	if (ql_alloc_small_buffers(qdev) != 0) {
		netdev_err(qdev->ndev, "ql_alloc_small_buffers failed\n");
		goto err_small_buffers;
	}

	if (ql_alloc_large_buffers(qdev) != 0) {
		netdev_err(qdev->ndev, "ql_alloc_large_buffers failed\n");
		goto err_small_buffers;
	}

	/* Initialize the large buffer queue. */
	ql_init_large_buffers(qdev);
	if (ql_create_send_free_list(qdev))
		goto err_free_list;

	qdev->rsp_current = qdev->rsp_q_virt_addr;

	return 0;
err_free_list:
	ql_free_send_free_list(qdev);
err_small_buffers:
	ql_free_buffer_queues(qdev);
err_buffer_queues:
	ql_free_net_req_rsp_queues(qdev);
err_req_rsp:
	pci_free_consistent(qdev->pdev,
			    PAGE_SIZE,
			    qdev->shadow_reg_virt_addr,
			    qdev->shadow_reg_phy_addr);

	return -ENOMEM;
}