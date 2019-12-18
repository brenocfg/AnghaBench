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
struct gvp11_hostdata {TYPE_1__* regs; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned int CNTR; } ;

/* Variables and functions */
 unsigned int GVP11_DMAC_INT_PENDING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct gvp11_hostdata* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wd33c93_intr (struct Scsi_Host*) ; 

__attribute__((used)) static irqreturn_t gvp11_intr(int irq, void *data)
{
	struct Scsi_Host *instance = data;
	struct gvp11_hostdata *hdata = shost_priv(instance);
	unsigned int status = hdata->regs->CNTR;
	unsigned long flags;

	if (!(status & GVP11_DMAC_INT_PENDING))
		return IRQ_NONE;

	spin_lock_irqsave(instance->host_lock, flags);
	wd33c93_intr(instance);
	spin_unlock_irqrestore(instance->host_lock, flags);
	return IRQ_HANDLED;
}