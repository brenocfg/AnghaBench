#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* tty; } ;
struct TYPE_8__ {int mcr; int msr; scalar_t__ send_outstanding; TYPE_3__ port; } ;
typedef  TYPE_2__ modem_info ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_OUT2 ; 
 int UART_MCR_RTS ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DSR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdn_lock_drivers () ; 
 int /*<<< orphan*/  isdn_tty_change_speed (TYPE_2__*) ; 
 scalar_t__ tty_port_initialized (TYPE_3__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_3__*,int) ; 

__attribute__((used)) static int
isdn_tty_startup(modem_info *info)
{
	if (tty_port_initialized(&info->port))
		return 0;
	isdn_lock_drivers();
#ifdef ISDN_DEBUG_MODEM_OPEN
	printk(KERN_DEBUG "starting up ttyi%d ...\n", info->line);
#endif
	/*
	 * Now, initialize the UART
	 */
	info->mcr = UART_MCR_DTR | UART_MCR_RTS | UART_MCR_OUT2;
	if (info->port.tty)
		clear_bit(TTY_IO_ERROR, &info->port.tty->flags);
	/*
	 * and set the speed of the serial port
	 */
	isdn_tty_change_speed(info);

	tty_port_set_initialized(&info->port, 1);
	info->msr |= (UART_MSR_DSR | UART_MSR_CTS);
	info->send_outstanding = 0;
	return 0;
}