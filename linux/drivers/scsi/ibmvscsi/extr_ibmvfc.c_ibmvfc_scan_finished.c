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
struct ibmvfc_host {scalar_t__ scan_complete; int /*<<< orphan*/  dev; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned long) ; 
 unsigned long init_timeout ; 
 struct ibmvfc_host* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ibmvfc_scan_finished(struct Scsi_Host *shost, unsigned long time)
{
	unsigned long flags;
	struct ibmvfc_host *vhost = shost_priv(shost);
	int done = 0;

	spin_lock_irqsave(shost->host_lock, flags);
	if (time >= (init_timeout * HZ)) {
		dev_info(vhost->dev, "Scan taking longer than %d seconds, "
			 "continuing initialization\n", init_timeout);
		done = 1;
	}

	if (vhost->scan_complete)
		done = 1;
	spin_unlock_irqrestore(shost->host_lock, flags);
	return done;
}