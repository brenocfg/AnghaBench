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
struct scsi_device {scalar_t__ channel; struct myrs_pdev_info* hostdata; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  sdev_gendev; TYPE_2__* host; } ;
struct myrs_pdev_info {int raid_level; scalar_t__ dev_state; int /*<<< orphan*/  ldev_num; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; } ;
struct myrs_ldev_info {int raid_level; scalar_t__ dev_state; int /*<<< orphan*/  ldev_num; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; } ;
struct myrs_hba {TYPE_1__* ctlr_info; } ;
typedef  enum raid_level { ____Placeholder_raid_level } raid_level ;
struct TYPE_4__ {scalar_t__ max_channel; } ;
struct TYPE_3__ {scalar_t__ physchan_present; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ MYRS_DEVICE_ONLINE ; 
#define  MYRS_RAID_JBOD 139 
#define  MYRS_RAID_LEVEL0 138 
#define  MYRS_RAID_LEVEL1 137 
#define  MYRS_RAID_LEVEL3 136 
#define  MYRS_RAID_LEVEL3F 135 
#define  MYRS_RAID_LEVEL3L 134 
#define  MYRS_RAID_LEVEL5 133 
#define  MYRS_RAID_LEVEL5L 132 
#define  MYRS_RAID_LEVEL6 131 
#define  MYRS_RAID_LEVELE 130 
#define  MYRS_RAID_NEWSPAN 129 
#define  MYRS_RAID_SPAN 128 
 unsigned char MYRS_STATUS_SUCCESS ; 
 int RAID_LEVEL_1 ; 
 int RAID_LEVEL_3 ; 
 int RAID_LEVEL_5 ; 
 int RAID_LEVEL_6 ; 
 int RAID_LEVEL_JBOD ; 
 int RAID_LEVEL_LINEAR ; 
 int RAID_LEVEL_UNKNOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct myrs_pdev_info*) ; 
 struct myrs_pdev_info* kzalloc (int,int) ; 
 char* myrs_devstate_name (scalar_t__) ; 
 unsigned char myrs_get_ldev_info (struct myrs_hba*,unsigned short,struct myrs_pdev_info*) ; 
 unsigned char myrs_get_pdev_info (struct myrs_hba*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct myrs_pdev_info*) ; 
 int /*<<< orphan*/  myrs_raid_template ; 
 unsigned short myrs_translate_ldev (struct myrs_hba*,struct scsi_device*) ; 
 int /*<<< orphan*/  raid_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,char const*) ; 
 struct myrs_hba* shost_priv (TYPE_2__*) ; 

__attribute__((used)) static int myrs_slave_alloc(struct scsi_device *sdev)
{
	struct myrs_hba *cs = shost_priv(sdev->host);
	unsigned char status;

	if (sdev->channel > sdev->host->max_channel)
		return 0;

	if (sdev->channel >= cs->ctlr_info->physchan_present) {
		struct myrs_ldev_info *ldev_info;
		unsigned short ldev_num;

		if (sdev->lun > 0)
			return -ENXIO;

		ldev_num = myrs_translate_ldev(cs, sdev);

		ldev_info = kzalloc(sizeof(*ldev_info), GFP_KERNEL|GFP_DMA);
		if (!ldev_info)
			return -ENOMEM;

		status = myrs_get_ldev_info(cs, ldev_num, ldev_info);
		if (status != MYRS_STATUS_SUCCESS) {
			sdev->hostdata = NULL;
			kfree(ldev_info);
		} else {
			enum raid_level level;

			dev_dbg(&sdev->sdev_gendev,
				"Logical device mapping %d:%d:%d -> %d\n",
				ldev_info->channel, ldev_info->target,
				ldev_info->lun, ldev_info->ldev_num);

			sdev->hostdata = ldev_info;
			switch (ldev_info->raid_level) {
			case MYRS_RAID_LEVEL0:
				level = RAID_LEVEL_LINEAR;
				break;
			case MYRS_RAID_LEVEL1:
				level = RAID_LEVEL_1;
				break;
			case MYRS_RAID_LEVEL3:
			case MYRS_RAID_LEVEL3F:
			case MYRS_RAID_LEVEL3L:
				level = RAID_LEVEL_3;
				break;
			case MYRS_RAID_LEVEL5:
			case MYRS_RAID_LEVEL5L:
				level = RAID_LEVEL_5;
				break;
			case MYRS_RAID_LEVEL6:
				level = RAID_LEVEL_6;
				break;
			case MYRS_RAID_LEVELE:
			case MYRS_RAID_NEWSPAN:
			case MYRS_RAID_SPAN:
				level = RAID_LEVEL_LINEAR;
				break;
			case MYRS_RAID_JBOD:
				level = RAID_LEVEL_JBOD;
				break;
			default:
				level = RAID_LEVEL_UNKNOWN;
				break;
			}
			raid_set_level(myrs_raid_template,
				       &sdev->sdev_gendev, level);
			if (ldev_info->dev_state != MYRS_DEVICE_ONLINE) {
				const char *name;

				name = myrs_devstate_name(ldev_info->dev_state);
				sdev_printk(KERN_DEBUG, sdev,
					    "logical device in state %s\n",
					    name ? name : "Invalid");
			}
		}
	} else {
		struct myrs_pdev_info *pdev_info;

		pdev_info = kzalloc(sizeof(*pdev_info), GFP_KERNEL|GFP_DMA);
		if (!pdev_info)
			return -ENOMEM;

		status = myrs_get_pdev_info(cs, sdev->channel,
					    sdev->id, sdev->lun,
					    pdev_info);
		if (status != MYRS_STATUS_SUCCESS) {
			sdev->hostdata = NULL;
			kfree(pdev_info);
			return -ENXIO;
		}
		sdev->hostdata = pdev_info;
	}
	return 0;
}