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
struct ipr_ioa_cfg {TYPE_1__* host; scalar_t__ errors_logged; scalar_t__ in_reset_reload; int /*<<< orphan*/  reset_wait_q; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EIO ; 
 int /*<<< orphan*/  IPR_SHUTDOWN_NORMAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  ipr_initiate_ioa_reset (struct ipr_ioa_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t ipr_store_diagnostics(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)shost->hostdata;
	unsigned long lock_flags = 0;
	int rc = count;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	while (ioa_cfg->in_reset_reload) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	}

	ioa_cfg->errors_logged = 0;
	ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NORMAL);

	if (ioa_cfg->in_reset_reload) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);

		/* Wait for a second for any errors to be logged */
		msleep(1000);
	} else {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		return -EIO;
	}

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	if (ioa_cfg->in_reset_reload || ioa_cfg->errors_logged)
		rc = -EIO;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	return rc;
}