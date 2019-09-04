#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ql3_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/ * rsp_q_virt_addr; int /*<<< orphan*/  rsp_q_phy_addr; int /*<<< orphan*/  rsp_q_size; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * req_q_virt_addr; int /*<<< orphan*/  req_q_phy_addr; int /*<<< orphan*/  req_q_size; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ALLOC_REQ_RSP_Q_DONE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_free_net_req_rsp_queues(struct ql3_adapter *qdev)
{
	if (!test_bit(QL_ALLOC_REQ_RSP_Q_DONE, &qdev->flags)) {
		netdev_info(qdev->ndev, "Already done\n");
		return;
	}

	pci_free_consistent(qdev->pdev,
			    qdev->req_q_size,
			    qdev->req_q_virt_addr, qdev->req_q_phy_addr);

	qdev->req_q_virt_addr = NULL;

	pci_free_consistent(qdev->pdev,
			    qdev->rsp_q_size,
			    qdev->rsp_q_virt_addr, qdev->rsp_q_phy_addr);

	qdev->rsp_q_virt_addr = NULL;

	clear_bit(QL_ALLOC_REQ_RSP_Q_DONE, &qdev->flags);
}