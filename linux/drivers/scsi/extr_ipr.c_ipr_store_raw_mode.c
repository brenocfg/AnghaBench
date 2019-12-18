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
struct scsi_device {scalar_t__ hostdata; TYPE_1__* host; } ;
struct ipr_resource_entry {scalar_t__ raw_mode; scalar_t__ sdev; } ;
struct ipr_ioa_cfg {TYPE_2__* host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ ipr_is_af_dasd_device (struct ipr_resource_entry*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,scalar_t__,char*,char*) ; 
 scalar_t__ simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t ipr_store_raw_mode(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)sdev->host->hostdata;
	struct ipr_resource_entry *res;
	unsigned long lock_flags = 0;
	ssize_t len;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (struct ipr_resource_entry *)sdev->hostdata;
	if (res) {
		if (ipr_is_af_dasd_device(res)) {
			res->raw_mode = simple_strtoul(buf, NULL, 10);
			len = strlen(buf);
			if (res->sdev)
				sdev_printk(KERN_INFO, res->sdev, "raw mode is %s\n",
					res->raw_mode ? "enabled" : "disabled");
		} else
			len = -EINVAL;
	} else
		len = -ENXIO;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	return len;
}