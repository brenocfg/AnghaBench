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
struct TYPE_4__ {int /*<<< orphan*/  xchar; } ;

/* Variables and functions */
 TYPE_2__* ICOM_PORT ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace (TYPE_2__*,char*,char) ; 
 int /*<<< orphan*/  writeb (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icom_send_xchar(struct uart_port *port, char ch)
{
	unsigned char xdata;
	int index;
	unsigned long flags;

	trace(ICOM_PORT, "SEND_XCHAR", ch);

	/* wait .1 sec to send char */
	for (index = 0; index < 10; index++) {
		spin_lock_irqsave(&port->lock, flags);
		xdata = readb(&ICOM_PORT->dram->xchar);
		if (xdata == 0x00) {
			trace(ICOM_PORT, "QUICK_WRITE", 0);
			writeb(ch, &ICOM_PORT->dram->xchar);

			/* flush write operation */
			xdata = readb(&ICOM_PORT->dram->xchar);
			spin_unlock_irqrestore(&port->lock, flags);
			break;
		}
		spin_unlock_irqrestore(&port->lock, flags);
		msleep(10);
	}
}