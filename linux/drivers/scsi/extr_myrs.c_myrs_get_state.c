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
struct scsi_device {scalar_t__ channel; struct myrs_ldev_info* hostdata; int /*<<< orphan*/  host; } ;
struct myrs_ldev_info {int dev_state; } ;
struct myrs_hba {TYPE_1__* ctlr_info; } ;
struct device {int dummy; } ;
typedef  enum raid_state { ____Placeholder_raid_state } raid_state ;
struct TYPE_2__ {scalar_t__ physchan_present; } ;

/* Variables and functions */
#define  MYRS_DEVICE_CRITICAL 133 
#define  MYRS_DEVICE_INVALID_STATE 132 
#define  MYRS_DEVICE_ONLINE 131 
#define  MYRS_DEVICE_REBUILD 130 
#define  MYRS_DEVICE_SUSPECTED_CRITICAL 129 
#define  MYRS_DEVICE_UNCONFIGURED 128 
 int RAID_STATE_ACTIVE ; 
 int RAID_STATE_DEGRADED ; 
 int RAID_STATE_OFFLINE ; 
 int RAID_STATE_RESYNCING ; 
 int RAID_STATE_UNKNOWN ; 
 int /*<<< orphan*/  myrs_raid_template ; 
 int /*<<< orphan*/  raid_set_state (int /*<<< orphan*/ ,struct device*,int) ; 
 struct myrs_hba* shost_priv (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static void
myrs_get_state(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct myrs_hba *cs = shost_priv(sdev->host);
	struct myrs_ldev_info *ldev_info = sdev->hostdata;
	enum raid_state state = RAID_STATE_UNKNOWN;

	if (sdev->channel < cs->ctlr_info->physchan_present || !ldev_info)
		state = RAID_STATE_UNKNOWN;
	else {
		switch (ldev_info->dev_state) {
		case MYRS_DEVICE_ONLINE:
			state = RAID_STATE_ACTIVE;
			break;
		case MYRS_DEVICE_SUSPECTED_CRITICAL:
		case MYRS_DEVICE_CRITICAL:
			state = RAID_STATE_DEGRADED;
			break;
		case MYRS_DEVICE_REBUILD:
			state = RAID_STATE_RESYNCING;
			break;
		case MYRS_DEVICE_UNCONFIGURED:
		case MYRS_DEVICE_INVALID_STATE:
			state = RAID_STATE_UNKNOWN;
			break;
		default:
			state = RAID_STATE_OFFLINE;
		}
	}
	raid_set_state(myrs_raid_template, dev, state);
}