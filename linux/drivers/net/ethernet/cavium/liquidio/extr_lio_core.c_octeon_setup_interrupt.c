#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int pf_srn; int trs; } ;
struct octeon_device {int num_msix_irqs; char* irq_name_storage; char* msix_entries; int octeon_id; int pf_num; int vf_num; int flags; TYPE_2__* pci_dev; int /*<<< orphan*/  affinity_mask; struct octeon_device* ioq_vector; int /*<<< orphan*/  vector; TYPE_1__ sriov_info; scalar_t__ msix_on; } ;
struct msix_entry {int entry; int /*<<< orphan*/  vector; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTRNAMSIZ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 size_t IRQ_NAME_OFF (int) ; 
 int LIO_FLAG_MSI_ENABLED ; 
 int MAX_IOQ_INTERRUPTS_PER_PF ; 
 int MAX_IOQ_INTERRUPTS_PER_VF ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct octeon_device*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  liquidio_legacy_intr_handler ; 
 int /*<<< orphan*/  liquidio_msix_intr_handler ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_2__*) ; 
 int pci_enable_msi (TYPE_2__*) ; 
 int pci_enable_msix_range (TYPE_2__*,struct msix_entry*,int,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct octeon_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,...) ; 

int octeon_setup_interrupt(struct octeon_device *oct, u32 num_ioqs)
{
	struct msix_entry *msix_entries;
	char *queue_irq_names = NULL;
	int i, num_interrupts = 0;
	int num_alloc_ioq_vectors;
	char *aux_irq_name = NULL;
	int num_ioq_vectors;
	int irqret, err;

	if (oct->msix_on) {
		oct->num_msix_irqs = num_ioqs;
		if (OCTEON_CN23XX_PF(oct)) {
			num_interrupts = MAX_IOQ_INTERRUPTS_PER_PF + 1;

			/* one non ioq interrupt for handling
			 * sli_mac_pf_int_sum
			 */
			oct->num_msix_irqs += 1;
		} else if (OCTEON_CN23XX_VF(oct)) {
			num_interrupts = MAX_IOQ_INTERRUPTS_PER_VF;
		}

		/* allocate storage for the names assigned to each irq */
		oct->irq_name_storage =
			kcalloc(num_interrupts, INTRNAMSIZ, GFP_KERNEL);
		if (!oct->irq_name_storage) {
			dev_err(&oct->pci_dev->dev, "Irq name storage alloc failed...\n");
			return -ENOMEM;
		}

		queue_irq_names = oct->irq_name_storage;

		if (OCTEON_CN23XX_PF(oct))
			aux_irq_name = &queue_irq_names
				[IRQ_NAME_OFF(MAX_IOQ_INTERRUPTS_PER_PF)];

		oct->msix_entries = kcalloc(oct->num_msix_irqs,
					    sizeof(struct msix_entry),
					    GFP_KERNEL);
		if (!oct->msix_entries) {
			dev_err(&oct->pci_dev->dev, "Memory Alloc failed...\n");
			kfree(oct->irq_name_storage);
			oct->irq_name_storage = NULL;
			return -ENOMEM;
		}

		msix_entries = (struct msix_entry *)oct->msix_entries;

		/*Assumption is that pf msix vectors start from pf srn to pf to
		 * trs and not from 0. if not change this code
		 */
		if (OCTEON_CN23XX_PF(oct)) {
			for (i = 0; i < oct->num_msix_irqs - 1; i++)
				msix_entries[i].entry =
					oct->sriov_info.pf_srn + i;

			msix_entries[oct->num_msix_irqs - 1].entry =
				oct->sriov_info.trs;
		} else if (OCTEON_CN23XX_VF(oct)) {
			for (i = 0; i < oct->num_msix_irqs; i++)
				msix_entries[i].entry = i;
		}
		num_alloc_ioq_vectors = pci_enable_msix_range(
						oct->pci_dev, msix_entries,
						oct->num_msix_irqs,
						oct->num_msix_irqs);
		if (num_alloc_ioq_vectors < 0) {
			dev_err(&oct->pci_dev->dev, "unable to Allocate MSI-X interrupts\n");
			kfree(oct->msix_entries);
			oct->msix_entries = NULL;
			kfree(oct->irq_name_storage);
			oct->irq_name_storage = NULL;
			return num_alloc_ioq_vectors;
		}

		dev_dbg(&oct->pci_dev->dev, "OCTEON: Enough MSI-X interrupts are allocated...\n");

		num_ioq_vectors = oct->num_msix_irqs;
		/** For PF, there is one non-ioq interrupt handler */
		if (OCTEON_CN23XX_PF(oct)) {
			num_ioq_vectors -= 1;

			snprintf(aux_irq_name, INTRNAMSIZ,
				 "LiquidIO%u-pf%u-aux", oct->octeon_id,
				 oct->pf_num);
			irqret = request_irq(
					msix_entries[num_ioq_vectors].vector,
					liquidio_legacy_intr_handler, 0,
					aux_irq_name, oct);
			if (irqret) {
				dev_err(&oct->pci_dev->dev,
					"Request_irq failed for MSIX interrupt Error: %d\n",
					irqret);
				pci_disable_msix(oct->pci_dev);
				kfree(oct->msix_entries);
				kfree(oct->irq_name_storage);
				oct->irq_name_storage = NULL;
				oct->msix_entries = NULL;
				return irqret;
			}
		}
		for (i = 0 ; i < num_ioq_vectors ; i++) {
			if (OCTEON_CN23XX_PF(oct))
				snprintf(&queue_irq_names[IRQ_NAME_OFF(i)],
					 INTRNAMSIZ, "LiquidIO%u-pf%u-rxtx-%u",
					 oct->octeon_id, oct->pf_num, i);

			if (OCTEON_CN23XX_VF(oct))
				snprintf(&queue_irq_names[IRQ_NAME_OFF(i)],
					 INTRNAMSIZ, "LiquidIO%u-vf%u-rxtx-%u",
					 oct->octeon_id, oct->vf_num, i);

			irqret = request_irq(msix_entries[i].vector,
					     liquidio_msix_intr_handler, 0,
					     &queue_irq_names[IRQ_NAME_OFF(i)],
					     &oct->ioq_vector[i]);

			if (irqret) {
				dev_err(&oct->pci_dev->dev,
					"Request_irq failed for MSIX interrupt Error: %d\n",
					irqret);
				/** Freeing the non-ioq irq vector here . */
				free_irq(msix_entries[num_ioq_vectors].vector,
					 oct);

				while (i) {
					i--;
					/** clearing affinity mask. */
					irq_set_affinity_hint(
						      msix_entries[i].vector,
						      NULL);
					free_irq(msix_entries[i].vector,
						 &oct->ioq_vector[i]);
				}
				pci_disable_msix(oct->pci_dev);
				kfree(oct->msix_entries);
				kfree(oct->irq_name_storage);
				oct->irq_name_storage = NULL;
				oct->msix_entries = NULL;
				return irqret;
			}
			oct->ioq_vector[i].vector = msix_entries[i].vector;
			/* assign the cpu mask for this msix interrupt vector */
			irq_set_affinity_hint(msix_entries[i].vector,
					      &oct->ioq_vector[i].affinity_mask
					      );
		}
		dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: MSI-X enabled\n",
			oct->octeon_id);
	} else {
		err = pci_enable_msi(oct->pci_dev);
		if (err)
			dev_warn(&oct->pci_dev->dev, "Reverting to legacy interrupts. Error: %d\n",
				 err);
		else
			oct->flags |= LIO_FLAG_MSI_ENABLED;

		/* allocate storage for the names assigned to the irq */
		oct->irq_name_storage = kcalloc(1, INTRNAMSIZ, GFP_KERNEL);
		if (!oct->irq_name_storage)
			return -ENOMEM;

		queue_irq_names = oct->irq_name_storage;

		if (OCTEON_CN23XX_PF(oct))
			snprintf(&queue_irq_names[IRQ_NAME_OFF(0)], INTRNAMSIZ,
				 "LiquidIO%u-pf%u-rxtx-%u",
				 oct->octeon_id, oct->pf_num, 0);

		if (OCTEON_CN23XX_VF(oct))
			snprintf(&queue_irq_names[IRQ_NAME_OFF(0)], INTRNAMSIZ,
				 "LiquidIO%u-vf%u-rxtx-%u",
				 oct->octeon_id, oct->vf_num, 0);

		irqret = request_irq(oct->pci_dev->irq,
				     liquidio_legacy_intr_handler,
				     IRQF_SHARED,
				     &queue_irq_names[IRQ_NAME_OFF(0)], oct);
		if (irqret) {
			if (oct->flags & LIO_FLAG_MSI_ENABLED)
				pci_disable_msi(oct->pci_dev);
			dev_err(&oct->pci_dev->dev, "Request IRQ failed with code: %d\n",
				irqret);
			kfree(oct->irq_name_storage);
			oct->irq_name_storage = NULL;
			return irqret;
		}
	}
	return 0;
}