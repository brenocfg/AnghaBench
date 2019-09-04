#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* disable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;} ;
struct octeon_device {int ifcount; int num_msix_irqs; TYPE_3__* pci_dev; int /*<<< orphan*/  status; int /*<<< orphan*/ * msix_entries; int /*<<< orphan*/ * ioq_vector; scalar_t__ msix_on; TYPE_2__ fn_list; TYPE_1__* props; } ;
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_ALL_INTR ; 
 int /*<<< orphan*/  OCT_DEV_IN_RESET ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_aer_uncorrect_error_status (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_get_state_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_free_ioq_vector (struct octeon_device*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_3__*) ; 
 int /*<<< orphan*/  pcierror_quiesce_device (struct octeon_device*) ; 
 int /*<<< orphan*/  stub1 (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_pci_io(struct octeon_device *oct)
{
	struct msix_entry *msix_entries;
	int i;

	/* No more instructions will be forwarded. */
	atomic_set(&oct->status, OCT_DEV_IN_RESET);

	for (i = 0; i < oct->ifcount; i++)
		netif_device_detach(oct->props[i].netdev);

	/* Disable interrupts  */
	oct->fn_list.disable_interrupt(oct, OCTEON_ALL_INTR);

	pcierror_quiesce_device(oct);
	if (oct->msix_on) {
		msix_entries = (struct msix_entry *)oct->msix_entries;
		for (i = 0; i < oct->num_msix_irqs; i++) {
			/* clear the affinity_cpumask */
			irq_set_affinity_hint(msix_entries[i].vector,
					      NULL);
			free_irq(msix_entries[i].vector,
				 &oct->ioq_vector[i]);
		}
		pci_disable_msix(oct->pci_dev);
		kfree(oct->msix_entries);
		oct->msix_entries = NULL;
		octeon_free_ioq_vector(oct);
	}
	dev_dbg(&oct->pci_dev->dev, "Device state is now %s\n",
		lio_get_state_string(&oct->status));

	/* making it a common function for all OCTEON models */
	cleanup_aer_uncorrect_error_status(oct->pci_dev);

	pci_disable_device(oct->pci_dev);
}