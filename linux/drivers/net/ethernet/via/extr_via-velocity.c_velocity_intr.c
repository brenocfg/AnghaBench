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
typedef  int u32 ;
struct velocity_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; int /*<<< orphan*/  mac_regs; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ISR_PPRXI ; 
 int ISR_PPTXI ; 
 int ISR_PRXI ; 
 int ISR_PTXI ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_disable_int (int /*<<< orphan*/ ) ; 
 int mac_read_isr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_write_isr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  velocity_error (struct velocity_info*,int) ; 

__attribute__((used)) static irqreturn_t velocity_intr(int irq, void *dev_instance)
{
	struct net_device *dev = dev_instance;
	struct velocity_info *vptr = netdev_priv(dev);
	u32 isr_status;

	spin_lock(&vptr->lock);
	isr_status = mac_read_isr(vptr->mac_regs);

	/* Not us ? */
	if (isr_status == 0) {
		spin_unlock(&vptr->lock);
		return IRQ_NONE;
	}

	/* Ack the interrupt */
	mac_write_isr(vptr->mac_regs, isr_status);

	if (likely(napi_schedule_prep(&vptr->napi))) {
		mac_disable_int(vptr->mac_regs);
		__napi_schedule(&vptr->napi);
	}

	if (isr_status & (~(ISR_PRXI | ISR_PPRXI | ISR_PTXI | ISR_PPTXI)))
		velocity_error(vptr, isr_status);

	spin_unlock(&vptr->lock);

	return IRQ_HANDLED;
}