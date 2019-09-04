#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* tty; } ;
struct TYPE_11__ {int* mdmreg; } ;
struct TYPE_13__ {int mcr; TYPE_5__ port; TYPE_2__ emu; int /*<<< orphan*/  msr; } ;
typedef  TYPE_4__ modem_info ;
struct TYPE_10__ {int c_cflag; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; TYPE_1__ termios; } ;

/* Variables and functions */
 int BIT_DTRHUP ; 
 int HUPCL ; 
 size_t REG_DTRHUP ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  UART_MSR_RI ; 
 int /*<<< orphan*/  isdn_tty_modem_hup (TYPE_4__*,int) ; 
 int /*<<< orphan*/  isdn_tty_modem_reset_regs (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdn_unlock_drivers () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_initialized (TYPE_5__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isdn_tty_shutdown(modem_info *info)
{
	if (!tty_port_initialized(&info->port))
		return;
#ifdef ISDN_DEBUG_MODEM_OPEN
	printk(KERN_DEBUG "Shutting down isdnmodem port %d ....\n", info->line);
#endif
	isdn_unlock_drivers();
	info->msr &= ~UART_MSR_RI;
	if (!info->port.tty || (info->port.tty->termios.c_cflag & HUPCL)) {
		info->mcr &= ~(UART_MCR_DTR | UART_MCR_RTS);
		if (info->emu.mdmreg[REG_DTRHUP] & BIT_DTRHUP) {
			isdn_tty_modem_reset_regs(info, 0);
#ifdef ISDN_DEBUG_MODEM_HUP
			printk(KERN_DEBUG "Mhup in isdn_tty_shutdown\n");
#endif
			isdn_tty_modem_hup(info, 1);
		}
	}
	if (info->port.tty)
		set_bit(TTY_IO_ERROR, &info->port.tty->flags);

	tty_port_set_initialized(&info->port, 0);
}