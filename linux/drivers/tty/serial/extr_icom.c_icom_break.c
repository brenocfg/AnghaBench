#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {TYPE_1__* dram; } ;
struct TYPE_4__ {int /*<<< orphan*/  CmdReg; } ;

/* Variables and functions */
 unsigned char CMD_SND_BREAK ; 
 TYPE_2__* ICOM_PORT ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icom_break(struct uart_port *port, int break_state)
{
	unsigned char cmdReg;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	trace(ICOM_PORT, "BREAK", 0);
	cmdReg = readb(&ICOM_PORT->dram->CmdReg);
	if (break_state == -1) {
		writeb(cmdReg | CMD_SND_BREAK, &ICOM_PORT->dram->CmdReg);
	} else {
		writeb(cmdReg & ~CMD_SND_BREAK, &ICOM_PORT->dram->CmdReg);
	}
	spin_unlock_irqrestore(&port->lock, flags);
}