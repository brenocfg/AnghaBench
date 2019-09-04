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
typedef  int u32 ;
struct ql3_adapter {int req_q_size; int rsp_q_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  req_q_phy_addr; int /*<<< orphan*/ * req_q_virt_addr; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ndev; int /*<<< orphan*/  rsp_q_phy_addr; int /*<<< orphan*/ * rsp_q_virt_addr; } ;
struct ob_mac_iocb_req {int dummy; } ;
struct net_rsp_iocb {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int LS_64BITS (int /*<<< orphan*/ ) ; 
 int NUM_REQ_Q_ENTRIES ; 
 int NUM_RSP_Q_ENTRIES ; 
 int /*<<< orphan*/  QL_ALLOC_REQ_RSP_Q_DONE ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ql_alloc_net_req_rsp_queues(struct ql3_adapter *qdev)
{
	qdev->req_q_size =
	    (u32) (NUM_REQ_Q_ENTRIES * sizeof(struct ob_mac_iocb_req));

	qdev->rsp_q_size = NUM_RSP_Q_ENTRIES * sizeof(struct net_rsp_iocb);

	/* The barrier is required to ensure request and response queue
	 * addr writes to the registers.
	 */
	wmb();

	qdev->req_q_virt_addr =
	    pci_alloc_consistent(qdev->pdev,
				 (size_t) qdev->req_q_size,
				 &qdev->req_q_phy_addr);

	if ((qdev->req_q_virt_addr == NULL) ||
	    LS_64BITS(qdev->req_q_phy_addr) & (qdev->req_q_size - 1)) {
		netdev_err(qdev->ndev, "reqQ failed\n");
		return -ENOMEM;
	}

	qdev->rsp_q_virt_addr =
	    pci_alloc_consistent(qdev->pdev,
				 (size_t) qdev->rsp_q_size,
				 &qdev->rsp_q_phy_addr);

	if ((qdev->rsp_q_virt_addr == NULL) ||
	    LS_64BITS(qdev->rsp_q_phy_addr) & (qdev->rsp_q_size - 1)) {
		netdev_err(qdev->ndev, "rspQ allocation failed\n");
		pci_free_consistent(qdev->pdev, (size_t) qdev->req_q_size,
				    qdev->req_q_virt_addr,
				    qdev->req_q_phy_addr);
		return -ENOMEM;
	}

	set_bit(QL_ALLOC_REQ_RSP_Q_DONE, &qdev->flags);

	return 0;
}