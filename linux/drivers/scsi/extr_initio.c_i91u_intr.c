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
struct initio_host {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int initio_isr (struct initio_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t i91u_intr(int irqno, void *dev_id)
{
	struct Scsi_Host *dev = dev_id;
	unsigned long flags;
	int r;
	
	spin_lock_irqsave(dev->host_lock, flags);
	r = initio_isr((struct initio_host *)dev->hostdata);
	spin_unlock_irqrestore(dev->host_lock, flags);
	if (r)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}