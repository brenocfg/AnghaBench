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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct scsi_device {scalar_t__ channel; struct myrs_ldev_info* hostdata; int /*<<< orphan*/  host; } ;
struct myrs_ldev_info {unsigned short ldev_num; int rbld_lba; int /*<<< orphan*/  cfg_devsize; scalar_t__ rbld_active; } ;
struct myrs_hba {TYPE_1__* ctlr_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ physchan_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myrs_get_ldev_info (struct myrs_hba*,unsigned short,struct myrs_ldev_info*) ; 
 int /*<<< orphan*/  myrs_raid_template ; 
 int /*<<< orphan*/  raid_set_resync (int /*<<< orphan*/ ,struct device*,int) ; 
 struct myrs_hba* shost_priv (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static void
myrs_get_resync(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct myrs_hba *cs = shost_priv(sdev->host);
	struct myrs_ldev_info *ldev_info = sdev->hostdata;
	u64 percent_complete = 0;
	u8 status;

	if (sdev->channel < cs->ctlr_info->physchan_present || !ldev_info)
		return;
	if (ldev_info->rbld_active) {
		unsigned short ldev_num = ldev_info->ldev_num;

		status = myrs_get_ldev_info(cs, ldev_num, ldev_info);
		percent_complete = ldev_info->rbld_lba * 100;
		do_div(percent_complete, ldev_info->cfg_devsize);
	}
	raid_set_resync(myrs_raid_template, dev, percent_complete);
}