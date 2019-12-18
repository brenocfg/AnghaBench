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
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ host_eh_scheduled; scalar_t__ host_failed; int /*<<< orphan*/  host_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  scsi_eh_wakeup (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_host_in_recovery (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_dec_host_busy(struct Scsi_Host *shost)
{
	unsigned long flags;

	rcu_read_lock();
	atomic_dec(&shost->host_busy);
	if (unlikely(scsi_host_in_recovery(shost))) {
		spin_lock_irqsave(shost->host_lock, flags);
		if (shost->host_failed || shost->host_eh_scheduled)
			scsi_eh_wakeup(shost);
		spin_unlock_irqrestore(shost->host_lock, flags);
	}
	rcu_read_unlock();
}