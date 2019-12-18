#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_device {struct myrb_pdev_state* hostdata; int /*<<< orphan*/  host; } ;
struct myrb_pdev_state {int state; int /*<<< orphan*/  present; } ;
struct myrb_hba {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum myrb_devstate { ____Placeholder_myrb_devstate } myrb_devstate ;

/* Variables and functions */
 size_t EAGAIN ; 
 size_t EBUSY ; 
 size_t EINVAL ; 
 size_t EIO ; 
 size_t ENODEV ; 
 size_t ENXIO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MYRB_DEVICE_DEAD ; 
 int MYRB_DEVICE_ONLINE ; 
 int MYRB_DEVICE_STANDBY ; 
#define  MYRB_STATUS_CHANNEL_BUSY 132 
#define  MYRB_STATUS_INVALID_CHANNEL_OR_TARGET 131 
#define  MYRB_STATUS_NO_DEVICE 130 
#define  MYRB_STATUS_START_DEVICE_FAILED 129 
#define  MYRB_STATUS_SUCCESS 128 
 unsigned short myrb_set_pdev_state (struct myrb_hba*,struct scsi_device*,int) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,...) ; 
 struct myrb_hba* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t raid_state_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct myrb_hba *cb = shost_priv(sdev->host);
	struct myrb_pdev_state *pdev_info;
	enum myrb_devstate new_state;
	unsigned short status;

	if (!strncmp(buf, "kill", 4) ||
	    !strncmp(buf, "offline", 7))
		new_state = MYRB_DEVICE_DEAD;
	else if (!strncmp(buf, "online", 6))
		new_state = MYRB_DEVICE_ONLINE;
	else if (!strncmp(buf, "standby", 7))
		new_state = MYRB_DEVICE_STANDBY;
	else
		return -EINVAL;

	pdev_info = sdev->hostdata;
	if (!pdev_info) {
		sdev_printk(KERN_INFO, sdev,
			    "Failed - no physical device information\n");
		return -ENXIO;
	}
	if (!pdev_info->present) {
		sdev_printk(KERN_INFO, sdev,
			    "Failed - device not present\n");
		return -ENXIO;
	}

	if (pdev_info->state == new_state)
		return count;

	status = myrb_set_pdev_state(cb, sdev, new_state);
	switch (status) {
	case MYRB_STATUS_SUCCESS:
		break;
	case MYRB_STATUS_START_DEVICE_FAILED:
		sdev_printk(KERN_INFO, sdev,
			     "Failed - Unable to Start Device\n");
		count = -EAGAIN;
		break;
	case MYRB_STATUS_NO_DEVICE:
		sdev_printk(KERN_INFO, sdev,
			    "Failed - No Device at Address\n");
		count = -ENODEV;
		break;
	case MYRB_STATUS_INVALID_CHANNEL_OR_TARGET:
		sdev_printk(KERN_INFO, sdev,
			 "Failed - Invalid Channel or Target or Modifier\n");
		count = -EINVAL;
		break;
	case MYRB_STATUS_CHANNEL_BUSY:
		sdev_printk(KERN_INFO, sdev,
			 "Failed - Channel Busy\n");
		count = -EBUSY;
		break;
	default:
		sdev_printk(KERN_INFO, sdev,
			 "Failed - Unexpected Status %04X\n", status);
		count = -EIO;
		break;
	}
	return count;
}