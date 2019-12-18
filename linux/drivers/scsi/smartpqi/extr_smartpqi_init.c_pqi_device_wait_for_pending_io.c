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
struct pqi_scsi_dev {int /*<<< orphan*/  scsi_cmds_outstanding; } ;
struct pqi_ctrl_info {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int ETIMEDOUT ; 
 unsigned long NO_TIMEOUT ; 
 unsigned long PQI_HZ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pqi_check_ctrl_health (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pqi_device_wait_for_pending_io(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device, unsigned long timeout_secs)
{
	unsigned long timeout;

	timeout = (timeout_secs * PQI_HZ) + jiffies;

	while (atomic_read(&device->scsi_cmds_outstanding)) {
		pqi_check_ctrl_health(ctrl_info);
		if (pqi_ctrl_offline(ctrl_info))
			return -ENXIO;
		if (timeout_secs != NO_TIMEOUT) {
			if (time_after(jiffies, timeout)) {
				dev_err(&ctrl_info->pci_dev->dev,
					"timed out waiting for pending IO\n");
				return -ETIMEDOUT;
			}
		}
		usleep_range(1000, 2000);
	}

	return 0;
}