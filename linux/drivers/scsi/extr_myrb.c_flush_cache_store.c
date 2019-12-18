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
struct myrb_hba {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EIO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MYRB_CMD_FLUSH ; 
 unsigned short MYRB_STATUS_SUCCESS ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 unsigned short myrb_exec_type3 (struct myrb_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,...) ; 
 struct myrb_hba* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static ssize_t flush_cache_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct myrb_hba *cb = shost_priv(shost);
	unsigned short status;

	status = myrb_exec_type3(cb, MYRB_CMD_FLUSH, 0);
	if (status == MYRB_STATUS_SUCCESS) {
		shost_printk(KERN_INFO, shost,
			     "Cache Flush Completed\n");
		return count;
	}
	shost_printk(KERN_INFO, shost,
		     "Cache Flush Failed, status %x\n", status);
	return -EIO;
}