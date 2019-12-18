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
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int app_cap_flags; } ;
struct octeon_device {scalar_t__ app_mode; TYPE_2__* pci_dev; TYPE_1__ fw_info; int /*<<< orphan*/  octeon_id; scalar_t__ watchdog_task; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CVM_DRV_NIC_APP ; 
 int LIQUIDIO_SWITCHDEV_CAP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  lio_vf_rep_modexit () ; 
 int /*<<< orphan*/  liquidio_stop_nic_module (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_destroy_resources (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_free_device_mem (struct octeon_device*) ; 
 struct octeon_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void liquidio_remove(struct pci_dev *pdev)
{
	struct octeon_device *oct_dev = pci_get_drvdata(pdev);

	dev_dbg(&oct_dev->pci_dev->dev, "Stopping device\n");

	if (oct_dev->watchdog_task)
		kthread_stop(oct_dev->watchdog_task);

	if (!oct_dev->octeon_id &&
	    oct_dev->fw_info.app_cap_flags & LIQUIDIO_SWITCHDEV_CAP)
		lio_vf_rep_modexit();

	if (oct_dev->app_mode && (oct_dev->app_mode == CVM_DRV_NIC_APP))
		liquidio_stop_nic_module(oct_dev);

	/* Reset the octeon device and cleanup all memory allocated for
	 * the octeon device by driver.
	 */
	octeon_destroy_resources(oct_dev);

	dev_info(&oct_dev->pci_dev->dev, "Device removed\n");

	/* This octeon device has been removed. Update the global
	 * data structure to reflect this. Free the device structure.
	 */
	octeon_free_device_mem(oct_dev);
}