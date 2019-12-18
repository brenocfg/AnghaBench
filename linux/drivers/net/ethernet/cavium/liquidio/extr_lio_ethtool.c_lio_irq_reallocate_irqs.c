#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;} ;
struct octeon_device {int num_msix_irqs; TYPE_1__ fn_list; TYPE_2__* pci_dev; int /*<<< orphan*/ * irq_name_storage; int /*<<< orphan*/ * msix_entries; scalar_t__ vector; struct octeon_device* ioq_vector; scalar_t__ msix_on; } ;
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_ALL_INTR ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct octeon_device*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ octeon_allocate_ioq_vector (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_setup_interrupt (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lio_irq_reallocate_irqs(struct octeon_device *oct, uint32_t num_ioqs)
{
	struct msix_entry *msix_entries;
	int num_msix_irqs = 0;
	int i;

	if (!oct->msix_on)
		return 0;

	/* Disable the input and output queues now. No more packets will
	 * arrive from Octeon.
	 */
	oct->fn_list.disable_interrupt(oct, OCTEON_ALL_INTR);

	if (oct->msix_on) {
		if (OCTEON_CN23XX_PF(oct))
			num_msix_irqs = oct->num_msix_irqs - 1;
		else if (OCTEON_CN23XX_VF(oct))
			num_msix_irqs = oct->num_msix_irqs;

		msix_entries = (struct msix_entry *)oct->msix_entries;
		for (i = 0; i < num_msix_irqs; i++) {
			if (oct->ioq_vector[i].vector) {
				/* clear the affinity_cpumask */
				irq_set_affinity_hint(msix_entries[i].vector,
						      NULL);
				free_irq(msix_entries[i].vector,
					 &oct->ioq_vector[i]);
				oct->ioq_vector[i].vector = 0;
			}
		}

		/* non-iov vector's argument is oct struct */
		if (OCTEON_CN23XX_PF(oct))
			free_irq(msix_entries[i].vector, oct);

		pci_disable_msix(oct->pci_dev);
		kfree(oct->msix_entries);
		oct->msix_entries = NULL;
	}

	kfree(oct->irq_name_storage);
	oct->irq_name_storage = NULL;

	if (octeon_allocate_ioq_vector(oct, num_ioqs)) {
		dev_err(&oct->pci_dev->dev, "OCTEON: ioq vector allocation failed\n");
		return -1;
	}

	if (octeon_setup_interrupt(oct, num_ioqs)) {
		dev_info(&oct->pci_dev->dev, "Setup interrupt failed\n");
		return -1;
	}

	/* Enable Octeon device interrupts */
	oct->fn_list.enable_interrupt(oct, OCTEON_ALL_INTR);

	return 0;
}