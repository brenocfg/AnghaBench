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
struct irq_affinity {int post_vectors; } ;
struct TYPE_2__ {int eqid_count; } ;
struct beiscsi_hba {int generation; int num_cpus; int /*<<< orphan*/  pcidev; TYPE_1__ fw_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_MAX_NUM_CPUS ; 
#define  BE_GEN2 130 
#define  BE_GEN3 129 
#define  BE_GEN4 128 
 int PCI_IRQ_AFFINITY ; 
 int PCI_IRQ_MSIX ; 
 scalar_t__ enable_msix ; 
 scalar_t__ pci_alloc_irq_vectors_affinity (int /*<<< orphan*/ ,int,int,int,struct irq_affinity*) ; 

__attribute__((used)) static void be2iscsi_enable_msix(struct beiscsi_hba *phba)
{
	int nvec = 1;

	switch (phba->generation) {
	case BE_GEN2:
	case BE_GEN3:
		nvec = BEISCSI_MAX_NUM_CPUS + 1;
		break;
	case BE_GEN4:
		nvec = phba->fw_config.eqid_count;
		break;
	default:
		nvec = 2;
		break;
	}

	/* if eqid_count == 1 fall back to INTX */
	if (enable_msix && nvec > 1) {
		struct irq_affinity desc = { .post_vectors = 1 };

		if (pci_alloc_irq_vectors_affinity(phba->pcidev, 2, nvec,
				PCI_IRQ_MSIX | PCI_IRQ_AFFINITY, &desc) < 0) {
			phba->num_cpus = nvec - 1;
			return;
		}
	}

	phba->num_cpus = 1;
}