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
struct gscps2port {int /*<<< orphan*/  lock; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ GSC_RESET ; 
 int /*<<< orphan*/  gscps2_flush (struct gscps2port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void gscps2_reset(struct gscps2port *ps2port)
{
	unsigned long flags;

	/* reset the interface */
	spin_lock_irqsave(&ps2port->lock, flags);
	gscps2_flush(ps2port);
	writeb(0xff, ps2port->addr + GSC_RESET);
	gscps2_flush(ps2port);
	spin_unlock_irqrestore(&ps2port->lock, flags);
}