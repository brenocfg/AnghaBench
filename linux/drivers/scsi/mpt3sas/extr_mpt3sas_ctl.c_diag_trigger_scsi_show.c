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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct SL_WH_SCSI_TRIGGERS_T {int dummy; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  diag_trigger_lock; int /*<<< orphan*/  diag_trigger_scsi; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t
diag_trigger_scsi_show(struct device *cdev,
	struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	unsigned long flags;
	ssize_t rc;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	rc = sizeof(struct SL_WH_SCSI_TRIGGERS_T);
	memcpy(buf, &ioc->diag_trigger_scsi, rc);
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	return rc;
}