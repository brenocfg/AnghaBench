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
struct orc_host {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  orc_interrupt (struct orc_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t inia100_intr(int irqno, void *devid)
{
	struct Scsi_Host *shost = (struct Scsi_Host *)devid;
	struct orc_host *host = (struct orc_host *)shost->hostdata;
	unsigned long flags;
	irqreturn_t res;

	spin_lock_irqsave(shost->host_lock, flags);
	res = orc_interrupt(host);
	spin_unlock_irqrestore(shost->host_lock, flags);

	return res;
}