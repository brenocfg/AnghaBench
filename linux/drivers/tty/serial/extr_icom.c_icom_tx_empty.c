#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {TYPE_2__* statStg; } ;
struct TYPE_5__ {TYPE_1__* xmit; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_3__* ICOM_PORT ; 
 int SA_FLAGS_READY_TO_XMIT ; 
 int TIOCSER_TEMT ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int icom_tx_empty(struct uart_port *port)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	if (cpu_to_le16(ICOM_PORT->statStg->xmit[0].flags) &
	    SA_FLAGS_READY_TO_XMIT)
		ret = TIOCSER_TEMT;
	else
		ret = 0;

	spin_unlock_irqrestore(&port->lock, flags);
	return ret;
}