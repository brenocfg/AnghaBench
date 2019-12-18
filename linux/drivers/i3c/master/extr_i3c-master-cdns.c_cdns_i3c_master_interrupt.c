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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct cdns_i3c_master {TYPE_1__ xferqueue; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MST_IMR ; 
 int MST_INT_IBIR_THR ; 
 scalar_t__ MST_ISR ; 
 int /*<<< orphan*/  cdns_i3c_master_end_xfer_locked (struct cdns_i3c_master*,int) ; 
 int /*<<< orphan*/  cnds_i3c_master_demux_ibis (struct cdns_i3c_master*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cdns_i3c_master_interrupt(int irq, void *data)
{
	struct cdns_i3c_master *master = data;
	u32 status;

	status = readl(master->regs + MST_ISR);
	if (!(status & readl(master->regs + MST_IMR)))
		return IRQ_NONE;

	spin_lock(&master->xferqueue.lock);
	cdns_i3c_master_end_xfer_locked(master, status);
	spin_unlock(&master->xferqueue.lock);

	if (status & MST_INT_IBIR_THR)
		cnds_i3c_master_demux_ibis(master);

	return IRQ_HANDLED;
}