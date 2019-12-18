#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* disable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;} ;
struct octeon_device {int flags; TYPE_2__* pci_dev; int /*<<< orphan*/  status; TYPE_1__ fn_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int LIO_FLAG_MSI_ENABLED ; 
 int /*<<< orphan*/  OCTEON_ALL_INTR ; 
 int /*<<< orphan*/  OCT_DEV_IN_RESET ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_aer_uncorrect_error_status (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct octeon_device*) ; 
 int /*<<< orphan*/  lio_get_state_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_2__*) ; 
 int /*<<< orphan*/  pcierror_quiesce_device (struct octeon_device*) ; 
 int /*<<< orphan*/  stub1 (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_pci_io(struct octeon_device *oct)
{
	/* No more instructions will be forwarded. */
	atomic_set(&oct->status, OCT_DEV_IN_RESET);

	pci_disable_device(oct->pci_dev);

	/* Disable interrupts  */
	oct->fn_list.disable_interrupt(oct, OCTEON_ALL_INTR);

	pcierror_quiesce_device(oct);

	/* Release the interrupt line */
	free_irq(oct->pci_dev->irq, oct);

	if (oct->flags & LIO_FLAG_MSI_ENABLED)
		pci_disable_msi(oct->pci_dev);

	dev_dbg(&oct->pci_dev->dev, "Device state is now %s\n",
		lio_get_state_string(&oct->status));

	/* making it a common function for all OCTEON models */
	cleanup_aer_uncorrect_error_status(oct->pci_dev);
}