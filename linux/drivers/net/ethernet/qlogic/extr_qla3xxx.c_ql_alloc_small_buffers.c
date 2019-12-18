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
struct ql3_adapter {int small_buf_total_size; int /*<<< orphan*/  flags; scalar_t__ small_buf_index; scalar_t__ small_buf_phy_addr_low; scalar_t__ small_buf_phy_addr_high; struct bufq_addr_element* small_buf_q_virt_addr; int /*<<< orphan*/  small_buf_phy_addr; int /*<<< orphan*/  ndev; int /*<<< orphan*/ * small_buf_virt_addr; int /*<<< orphan*/  pdev; } ;
struct bufq_addr_element {void* addr_low; void* addr_high; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ LS_64BITS (int /*<<< orphan*/ ) ; 
 scalar_t__ MS_64BITS (int /*<<< orphan*/ ) ; 
 int NUM_SBUFQ_ENTRIES ; 
 int QL_ADDR_ELE_PER_BUFQ_ENTRY ; 
 int /*<<< orphan*/  QL_ALLOC_SMALL_BUF_DONE ; 
 int QL_SMALL_BUFFER_SIZE ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_alloc_small_buffers(struct ql3_adapter *qdev)
{
	int i;
	struct bufq_addr_element *small_buf_q_entry;

	/* Currently we allocate on one of memory and use it for smallbuffers */
	qdev->small_buf_total_size =
		(QL_ADDR_ELE_PER_BUFQ_ENTRY * NUM_SBUFQ_ENTRIES *
		 QL_SMALL_BUFFER_SIZE);

	qdev->small_buf_virt_addr =
		pci_alloc_consistent(qdev->pdev,
				     qdev->small_buf_total_size,
				     &qdev->small_buf_phy_addr);

	if (qdev->small_buf_virt_addr == NULL) {
		netdev_err(qdev->ndev, "Failed to get small buffer memory\n");
		return -ENOMEM;
	}

	qdev->small_buf_phy_addr_low = LS_64BITS(qdev->small_buf_phy_addr);
	qdev->small_buf_phy_addr_high = MS_64BITS(qdev->small_buf_phy_addr);

	small_buf_q_entry = qdev->small_buf_q_virt_addr;

	/* Initialize the small buffer queue. */
	for (i = 0; i < (QL_ADDR_ELE_PER_BUFQ_ENTRY * NUM_SBUFQ_ENTRIES); i++) {
		small_buf_q_entry->addr_high =
		    cpu_to_le32(qdev->small_buf_phy_addr_high);
		small_buf_q_entry->addr_low =
		    cpu_to_le32(qdev->small_buf_phy_addr_low +
				(i * QL_SMALL_BUFFER_SIZE));
		small_buf_q_entry++;
	}
	qdev->small_buf_index = 0;
	set_bit(QL_ALLOC_SMALL_BUF_DONE, &qdev->flags);
	return 0;
}