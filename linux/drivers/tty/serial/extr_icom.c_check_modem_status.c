#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; TYPE_4__* state; TYPE_2__ icount; } ;
struct icom_port {TYPE_5__ uart_port; TYPE_1__* dram; } ;
struct TYPE_9__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_10__ {TYPE_3__ port; } ;
struct TYPE_7__ {int /*<<< orphan*/  isr; } ;

/* Variables and functions */
 char ICOM_CTS ; 
 char ICOM_DCD ; 
 char ICOM_DSR ; 
 char ICOM_RI ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (struct icom_port*,char*,unsigned char) ; 
 int /*<<< orphan*/  uart_handle_cts_change (TYPE_5__*,char) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (TYPE_5__*,char) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void check_modem_status(struct icom_port *icom_port)
{
	static char old_status = 0;
	char delta_status;
	unsigned char status;

	spin_lock(&icom_port->uart_port.lock);

	/*modem input register */
	status = readb(&icom_port->dram->isr);
	trace(icom_port, "CHECK_MODEM", status);
	delta_status = status ^ old_status;
	if (delta_status) {
		if (delta_status & ICOM_RI)
			icom_port->uart_port.icount.rng++;
		if (delta_status & ICOM_DSR)
			icom_port->uart_port.icount.dsr++;
		if (delta_status & ICOM_DCD)
			uart_handle_dcd_change(&icom_port->uart_port,
					       delta_status & ICOM_DCD);
		if (delta_status & ICOM_CTS)
			uart_handle_cts_change(&icom_port->uart_port,
					       delta_status & ICOM_CTS);

		wake_up_interruptible(&icom_port->uart_port.state->
				      port.delta_msr_wait);
		old_status = status;
	}
	spin_unlock(&icom_port->uart_port.lock);
}