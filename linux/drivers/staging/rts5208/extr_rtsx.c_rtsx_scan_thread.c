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
struct rtsx_dev {int /*<<< orphan*/  scanning_done; TYPE_1__* pci; int /*<<< orphan*/  delay_wait; struct rtsx_chip* chip; } ;
struct rtsx_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_DRIVER_NAME ; 
 int HZ ; 
 int /*<<< orphan*/  RTSX_STAT_DISCONNECT ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int delay_use ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_chk_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_to_host (struct rtsx_dev*) ; 
 int /*<<< orphan*/  scsi_scan_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtsx_scan_thread(void *__dev)
{
	struct rtsx_dev *dev = __dev;
	struct rtsx_chip *chip = dev->chip;

	/* Wait for the timeout to expire or for a disconnect */
	if (delay_use > 0) {
		dev_info(&dev->pci->dev,
			 "%s: waiting for device to settle before scanning\n",
			 CR_DRIVER_NAME);
		wait_event_interruptible_timeout
			(dev->delay_wait,
			 rtsx_chk_stat(chip, RTSX_STAT_DISCONNECT),
			 delay_use * HZ);
	}

	/* If the device is still connected, perform the scanning */
	if (!rtsx_chk_stat(chip, RTSX_STAT_DISCONNECT)) {
		scsi_scan_host(rtsx_to_host(dev));
		dev_info(&dev->pci->dev, "%s: device scan complete\n",
			 CR_DRIVER_NAME);

		/* Should we unbind if no devices were detected? */
	}

	complete_and_exit(&dev->scanning_done, 0);
}