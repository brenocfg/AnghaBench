#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct SL_WH_MASTER_TRIGGER_T {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  MasterData; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  diag_trigger_lock; TYPE_1__ diag_trigger_master; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MASTER_TRIGGER_ADAPTER_RESET ; 
 int /*<<< orphan*/  MASTER_TRIGGER_FW_FAULT ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,size_t) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t
diag_trigger_master_store(struct device *cdev,
	struct device_attribute *attr, const char *buf, size_t count)

{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	unsigned long flags;
	ssize_t rc;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	rc = min(sizeof(struct SL_WH_MASTER_TRIGGER_T), count);
	memset(&ioc->diag_trigger_master, 0,
	    sizeof(struct SL_WH_MASTER_TRIGGER_T));
	memcpy(&ioc->diag_trigger_master, buf, rc);
	ioc->diag_trigger_master.MasterData |=
	    (MASTER_TRIGGER_FW_FAULT + MASTER_TRIGGER_ADAPTER_RESET);
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	return rc;
}