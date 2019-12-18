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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct asc_port {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_CTL ; 
 int ASC_CTL_RUN ; 
#define  UART_PM_STATE_OFF 129 
#define  UART_PM_STATE_ON 128 
 int asc_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asc_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct asc_port* to_asc_port (struct uart_port*) ; 

__attribute__((used)) static void asc_pm(struct uart_port *port, unsigned int state,
		unsigned int oldstate)
{
	struct asc_port *ascport = to_asc_port(port);
	unsigned long flags = 0;
	u32 ctl;

	switch (state) {
	case UART_PM_STATE_ON:
		clk_prepare_enable(ascport->clk);
		break;
	case UART_PM_STATE_OFF:
		/*
		 * Disable the ASC baud rate generator, which is as close as
		 * we can come to turning it off. Note this is not called with
		 * the port spinlock held.
		 */
		spin_lock_irqsave(&port->lock, flags);
		ctl = asc_in(port, ASC_CTL) & ~ASC_CTL_RUN;
		asc_out(port, ASC_CTL, ctl);
		spin_unlock_irqrestore(&port->lock, flags);
		clk_disable_unprepare(ascport->clk);
		break;
	}
}