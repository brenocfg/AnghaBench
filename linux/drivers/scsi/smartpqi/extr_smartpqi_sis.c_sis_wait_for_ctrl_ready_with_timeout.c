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
typedef  int u32 ;
struct pqi_ctrl_info {TYPE_1__* pci_dev; TYPE_2__* registers; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sis_mailbox; int /*<<< orphan*/  sis_firmware_status; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 unsigned int PQI_HZ ; 
 int SIS_CTRL_KERNEL_PANIC ; 
 int SIS_CTRL_KERNEL_UP ; 
 int /*<<< orphan*/  SIS_CTRL_READY_POLL_INTERVAL_MSECS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 unsigned int jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 unsigned int readl (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned int,unsigned long) ; 

__attribute__((used)) static int sis_wait_for_ctrl_ready_with_timeout(struct pqi_ctrl_info *ctrl_info,
	unsigned int timeout_secs)
{
	unsigned long timeout;
	u32 status;

	timeout = (timeout_secs * PQI_HZ) + jiffies;

	while (1) {
		status = readl(&ctrl_info->registers->sis_firmware_status);
		if (status != ~0) {
			if (status & SIS_CTRL_KERNEL_PANIC) {
				dev_err(&ctrl_info->pci_dev->dev,
					"controller is offline: status code 0x%x\n",
					readl(
					&ctrl_info->registers->sis_mailbox[7]));
				return -ENODEV;
			}
			if (status & SIS_CTRL_KERNEL_UP)
				break;
		}
		if (time_after(jiffies, timeout)) {
			dev_err(&ctrl_info->pci_dev->dev,
				"controller not ready after %u seconds\n",
				timeout_secs);
			return -ETIMEDOUT;
		}
		msleep(SIS_CTRL_READY_POLL_INTERVAL_MSECS);
	}

	return 0;
}