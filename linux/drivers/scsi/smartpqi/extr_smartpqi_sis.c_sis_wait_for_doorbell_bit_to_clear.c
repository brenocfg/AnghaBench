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
struct TYPE_4__ {int /*<<< orphan*/  sis_firmware_status; int /*<<< orphan*/  sis_host_to_ctrl_doorbell; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 unsigned long PQI_HZ ; 
 int SIS_CTRL_KERNEL_PANIC ; 
 unsigned long SIS_DOORBELL_BIT_CLEAR_TIMEOUT_SECS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 unsigned long jiffies ; 
 int readl (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sis_wait_for_doorbell_bit_to_clear(
	struct pqi_ctrl_info *ctrl_info, u32 bit)
{
	int rc = 0;
	u32 doorbell_register;
	unsigned long timeout;

	timeout = (SIS_DOORBELL_BIT_CLEAR_TIMEOUT_SECS * PQI_HZ) + jiffies;

	while (1) {
		doorbell_register =
			readl(&ctrl_info->registers->sis_host_to_ctrl_doorbell);
		if ((doorbell_register & bit) == 0)
			break;
		if (readl(&ctrl_info->registers->sis_firmware_status) &
			SIS_CTRL_KERNEL_PANIC) {
			rc = -ENODEV;
			break;
		}
		if (time_after(jiffies, timeout)) {
			dev_err(&ctrl_info->pci_dev->dev,
				"doorbell register bit 0x%x not cleared\n",
				bit);
			rc = -ETIMEDOUT;
			break;
		}
		usleep_range(1000, 2000);
	}

	return rc;
}