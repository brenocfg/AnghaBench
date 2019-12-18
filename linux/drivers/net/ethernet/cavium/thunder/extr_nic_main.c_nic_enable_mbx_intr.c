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
typedef  int /*<<< orphan*/  u64 ;
struct nicpf {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_MASK (int) ; 
 scalar_t__ NIC_PF_MAILBOX_ENA_W1S ; 
 scalar_t__ NIC_PF_MAILBOX_INT ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int pci_sriov_get_totalvfs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nic_enable_mbx_intr(struct nicpf *nic)
{
	int vf_cnt = pci_sriov_get_totalvfs(nic->pdev);

#define INTR_MASK(vfs) ((vfs < 64) ? (BIT_ULL(vfs) - 1) : (~0ull))

	/* Clear it, to avoid spurious interrupts (if any) */
	nic_reg_write(nic, NIC_PF_MAILBOX_INT, INTR_MASK(vf_cnt));

	/* Enable mailbox interrupt for all VFs */
	nic_reg_write(nic, NIC_PF_MAILBOX_ENA_W1S, INTR_MASK(vf_cnt));
	/* One mailbox intr enable reg per 64 VFs */
	if (vf_cnt > 64) {
		nic_reg_write(nic, NIC_PF_MAILBOX_INT + sizeof(u64),
			      INTR_MASK(vf_cnt - 64));
		nic_reg_write(nic, NIC_PF_MAILBOX_ENA_W1S + sizeof(u64),
			      INTR_MASK(vf_cnt - 64));
	}
}