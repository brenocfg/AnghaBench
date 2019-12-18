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
struct Scsi_Host {scalar_t__ host_failed; int /*<<< orphan*/  ehandler; int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_ERROR_RECOVERY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_host_busy (struct Scsi_Host*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 int /*<<< orphan*/  trace_scsi_eh_wakeup (struct Scsi_Host*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void scsi_eh_wakeup(struct Scsi_Host *shost)
{
	lockdep_assert_held(shost->host_lock);

	if (scsi_host_busy(shost) == shost->host_failed) {
		trace_scsi_eh_wakeup(shost);
		wake_up_process(shost->ehandler);
		SCSI_LOG_ERROR_RECOVERY(5, shost_printk(KERN_INFO, shost,
			"Waking error handler thread\n"));
	}
}