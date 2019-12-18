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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int RequestCredit; } ;
struct MPT3SAS_ADAPTER {TYPE_1__ facts; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t
fw_queue_depth_show(struct device *cdev, struct device_attribute *attr,
	char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	return snprintf(buf, PAGE_SIZE, "%02d\n", ioc->facts.RequestCredit);
}