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
typedef  scalar_t__ u32 ;
struct octeon_device {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR ; 
 int HZ ; 
 scalar_t__ OCTEON_PCI_IO_BUF_OWNER_HOST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ octeon_mem_access_ok (struct octeon_device*) ; 
 scalar_t__ octeon_read_device_mem32 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

int octeon_wait_for_bootloader(struct octeon_device *oct,
			       u32 wait_time_hundredths)
{
	dev_dbg(&oct->pci_dev->dev, "waiting %d0 ms for bootloader\n",
		wait_time_hundredths);

	if (octeon_mem_access_ok(oct))
		return -1;

	while (wait_time_hundredths > 0 &&
	       octeon_read_device_mem32(oct,
					BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR)
	       != OCTEON_PCI_IO_BUF_OWNER_HOST) {
		if (--wait_time_hundredths <= 0)
			return -1;
		schedule_timeout_uninterruptible(HZ / 100);
	}
	return 0;
}