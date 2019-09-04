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
struct ql3_adapter {int /*<<< orphan*/ * small_buf_virt_addr; int /*<<< orphan*/  small_buf_phy_addr; int /*<<< orphan*/  small_buf_total_size; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ndev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ALLOC_SMALL_BUF_DONE ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_free_small_buffers(struct ql3_adapter *qdev)
{
	if (!test_bit(QL_ALLOC_SMALL_BUF_DONE, &qdev->flags)) {
		netdev_info(qdev->ndev, "Already done\n");
		return;
	}
	if (qdev->small_buf_virt_addr != NULL) {
		pci_free_consistent(qdev->pdev,
				    qdev->small_buf_total_size,
				    qdev->small_buf_virt_addr,
				    qdev->small_buf_phy_addr);

		qdev->small_buf_virt_addr = NULL;
	}
}