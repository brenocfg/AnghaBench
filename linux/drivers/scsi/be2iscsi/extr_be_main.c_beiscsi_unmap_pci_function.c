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
struct beiscsi_hba {int /*<<< orphan*/ * pci_va; int /*<<< orphan*/ * db_va; int /*<<< orphan*/ * csr_va; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void beiscsi_unmap_pci_function(struct beiscsi_hba *phba)
{
	if (phba->csr_va) {
		iounmap(phba->csr_va);
		phba->csr_va = NULL;
	}
	if (phba->db_va) {
		iounmap(phba->db_va);
		phba->db_va = NULL;
	}
	if (phba->pci_va) {
		iounmap(phba->pci_va);
		phba->pci_va = NULL;
	}
}