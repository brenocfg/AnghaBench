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
struct ql_rcv_buf_cb {int dummy; } ;
struct ql3_adapter {int lrg_buf_q_size; int num_lbufq_entries; int lrg_buf_q_alloc_size; int small_buf_q_size; int small_buf_q_alloc_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  small_buf_q_alloc_phy_addr; int /*<<< orphan*/  small_buf_q_phy_addr; int /*<<< orphan*/ * small_buf_q_alloc_virt_addr; int /*<<< orphan*/ * small_buf_q_virt_addr; int /*<<< orphan*/  lrg_buf_q_alloc_phy_addr; int /*<<< orphan*/ * lrg_buf_q_alloc_virt_addr; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ndev; int /*<<< orphan*/  lrg_buf_q_phy_addr; int /*<<< orphan*/ * lrg_buf_q_virt_addr; int /*<<< orphan*/ * lrg_buf; int /*<<< orphan*/  num_large_buffers; } ;
struct lrg_buf_q_entry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_SBUFQ_ENTRIES ; 
 void* PAGE_SIZE ; 
 int /*<<< orphan*/  QL_ALLOC_BUFQS_DONE ; 
 int /*<<< orphan*/ * kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_alloc_buffer_queues(struct ql3_adapter *qdev)
{
	/* Create Large Buffer Queue */
	qdev->lrg_buf_q_size =
		qdev->num_lbufq_entries * sizeof(struct lrg_buf_q_entry);
	if (qdev->lrg_buf_q_size < PAGE_SIZE)
		qdev->lrg_buf_q_alloc_size = PAGE_SIZE;
	else
		qdev->lrg_buf_q_alloc_size = qdev->lrg_buf_q_size * 2;

	qdev->lrg_buf = kmalloc_array(qdev->num_large_buffers,
				      sizeof(struct ql_rcv_buf_cb),
				      GFP_KERNEL);
	if (qdev->lrg_buf == NULL)
		return -ENOMEM;

	qdev->lrg_buf_q_alloc_virt_addr =
		pci_alloc_consistent(qdev->pdev,
				     qdev->lrg_buf_q_alloc_size,
				     &qdev->lrg_buf_q_alloc_phy_addr);

	if (qdev->lrg_buf_q_alloc_virt_addr == NULL) {
		netdev_err(qdev->ndev, "lBufQ failed\n");
		return -ENOMEM;
	}
	qdev->lrg_buf_q_virt_addr = qdev->lrg_buf_q_alloc_virt_addr;
	qdev->lrg_buf_q_phy_addr = qdev->lrg_buf_q_alloc_phy_addr;

	/* Create Small Buffer Queue */
	qdev->small_buf_q_size =
		NUM_SBUFQ_ENTRIES * sizeof(struct lrg_buf_q_entry);
	if (qdev->small_buf_q_size < PAGE_SIZE)
		qdev->small_buf_q_alloc_size = PAGE_SIZE;
	else
		qdev->small_buf_q_alloc_size = qdev->small_buf_q_size * 2;

	qdev->small_buf_q_alloc_virt_addr =
		pci_alloc_consistent(qdev->pdev,
				     qdev->small_buf_q_alloc_size,
				     &qdev->small_buf_q_alloc_phy_addr);

	if (qdev->small_buf_q_alloc_virt_addr == NULL) {
		netdev_err(qdev->ndev, "Small Buffer Queue allocation failed\n");
		pci_free_consistent(qdev->pdev, qdev->lrg_buf_q_alloc_size,
				    qdev->lrg_buf_q_alloc_virt_addr,
				    qdev->lrg_buf_q_alloc_phy_addr);
		return -ENOMEM;
	}

	qdev->small_buf_q_virt_addr = qdev->small_buf_q_alloc_virt_addr;
	qdev->small_buf_q_phy_addr = qdev->small_buf_q_alloc_phy_addr;
	set_bit(QL_ALLOC_BUFQS_DONE, &qdev->flags);
	return 0;
}