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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct moxa_port {int DCDState; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (TYPE_1__*,int) ; 

__attribute__((used)) static void moxa_new_dcdstate(struct moxa_port *p, u8 dcd)
{
	unsigned long flags;
	dcd = !!dcd;

	spin_lock_irqsave(&p->port.lock, flags);
	if (dcd != p->DCDState) {
        	p->DCDState = dcd;
        	spin_unlock_irqrestore(&p->port.lock, flags);
		if (!dcd)
			tty_port_tty_hangup(&p->port, true);
	}
	else
		spin_unlock_irqrestore(&p->port.lock, flags);
}