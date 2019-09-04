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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ device; int subsystem_vendor; int subsystem_device; int /*<<< orphan*/  devfn; TYPE_1__* bus; scalar_t__ vendor; int /*<<< orphan*/  dev; } ;
struct octeon_device_priv {int dummy; } ;
struct octeon_device {int ptp_enable; int subsystem_id; size_t octeon_id; int rx_pause; int tx_pause; TYPE_2__* pci_dev; int /*<<< orphan*/ * watchdog_task; int /*<<< orphan*/  adapter_refcount; int /*<<< orphan*/  msix_on; } ;
struct handshake {int /*<<< orphan*/  init; struct pci_dev* pci_dev; int /*<<< orphan*/  started; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIO_FLAG_MSIX_ENABLED ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_PF_VID ; 
 scalar_t__ OCTEON_CN66XX ; 
 scalar_t__ OCTEON_CN68XX ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_stage ; 
 struct handshake* handshake ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_create (int /*<<< orphan*/ ,struct octeon_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  liquidio_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  liquidio_watchdog ; 
 struct octeon_device* octeon_allocate_device (scalar_t__,int) ; 
 scalar_t__ octeon_device_init (struct octeon_device*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct octeon_device*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
liquidio_probe(struct pci_dev *pdev,
	       const struct pci_device_id *ent __attribute__((unused)))
{
	struct octeon_device *oct_dev = NULL;
	struct handshake *hs;

	oct_dev = octeon_allocate_device(pdev->device,
					 sizeof(struct octeon_device_priv));
	if (!oct_dev) {
		dev_err(&pdev->dev, "Unable to allocate device\n");
		return -ENOMEM;
	}

	if (pdev->device == OCTEON_CN23XX_PF_VID)
		oct_dev->msix_on = LIO_FLAG_MSIX_ENABLED;

	/* Enable PTP for 6XXX Device */
	if (((pdev->device == OCTEON_CN66XX) ||
	     (pdev->device == OCTEON_CN68XX)))
		oct_dev->ptp_enable = true;
	else
		oct_dev->ptp_enable = false;

	dev_info(&pdev->dev, "Initializing device %x:%x.\n",
		 (u32)pdev->vendor, (u32)pdev->device);

	/* Assign octeon_device for this device to the private data area. */
	pci_set_drvdata(pdev, oct_dev);

	/* set linux specific device pointer */
	oct_dev->pci_dev = (void *)pdev;

	oct_dev->subsystem_id = pdev->subsystem_vendor |
		(pdev->subsystem_device << 16);

	hs = &handshake[oct_dev->octeon_id];
	init_completion(&hs->init);
	init_completion(&hs->started);
	hs->pci_dev = pdev;

	if (oct_dev->octeon_id == 0)
		/* first LiquidIO NIC is detected */
		complete(&first_stage);

	if (octeon_device_init(oct_dev)) {
		complete(&hs->init);
		liquidio_remove(pdev);
		return -ENOMEM;
	}

	if (OCTEON_CN23XX_PF(oct_dev)) {
		u8 bus, device, function;

		if (atomic_read(oct_dev->adapter_refcount) == 1) {
			/* Each NIC gets one watchdog kernel thread.  The first
			 * PF (of each NIC) that gets pci_driver->probe()'d
			 * creates that thread.
			 */
			bus = pdev->bus->number;
			device = PCI_SLOT(pdev->devfn);
			function = PCI_FUNC(pdev->devfn);
			oct_dev->watchdog_task = kthread_create(
			    liquidio_watchdog, oct_dev,
			    "liowd/%02hhx:%02hhx.%hhx", bus, device, function);
			if (!IS_ERR(oct_dev->watchdog_task)) {
				wake_up_process(oct_dev->watchdog_task);
			} else {
				oct_dev->watchdog_task = NULL;
				dev_err(&oct_dev->pci_dev->dev,
					"failed to create kernel_thread\n");
				liquidio_remove(pdev);
				return -1;
			}
		}
	}

	oct_dev->rx_pause = 1;
	oct_dev->tx_pause = 1;

	dev_dbg(&oct_dev->pci_dev->dev, "Device is ready\n");

	return 0;
}