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
struct scsi_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 unsigned int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t zfcp_sysfs_scsi_zfcp_failed_show(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	unsigned int status = atomic_read(&sdev_to_zfcp(sdev)->status);
	unsigned int failed = status & ZFCP_STATUS_COMMON_ERP_FAILED ? 1 : 0;

	return sprintf(buf, "%d\n", failed);
}