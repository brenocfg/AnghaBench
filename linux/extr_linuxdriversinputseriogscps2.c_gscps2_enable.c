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
typedef  int /*<<< orphan*/  u8 ;
struct gscps2port {int /*<<< orphan*/  addr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSC_CTRL_ENBL ; 
 int /*<<< orphan*/  gscps2_flush (struct gscps2port*) ; 
 int /*<<< orphan*/  gscps2_readb_control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gscps2_writeb_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_TBE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gscps2_enable(struct gscps2port *ps2port, int enable)
{
	unsigned long flags;
	u8 data;

	/* now enable/disable the port */
	spin_lock_irqsave(&ps2port->lock, flags);
	gscps2_flush(ps2port);
	data = gscps2_readb_control(ps2port->addr);
	if (enable)
		data |= GSC_CTRL_ENBL;
	else
		data &= ~GSC_CTRL_ENBL;
	gscps2_writeb_control(data, ps2port->addr);
	spin_unlock_irqrestore(&ps2port->lock, flags);
	wait_TBE(ps2port->addr);
	gscps2_flush(ps2port);
}