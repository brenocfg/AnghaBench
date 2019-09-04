#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct tty_port {TYPE_2__* tty; } ;
struct TYPE_11__ {int* mdmreg; } ;
struct TYPE_12__ {int ncarrier; scalar_t__ online; TYPE_3__ emu; int /*<<< orphan*/  mcr; struct tty_port port; } ;
typedef  TYPE_4__ modem_info ;
struct TYPE_9__ {int c_cflag; } ;
struct TYPE_10__ {TYPE_1__ termios; } ;

/* Variables and functions */
 int BIT_DTRHUP ; 
 int CBAUD ; 
 int CBAUDEX ; 
 int CLOCAL ; 
 int CSIZE ; 
 int CSTOPB ; 
 int PARENB ; 
 int PARODD ; 
 size_t REG_DTRHUP ; 
 int UART_LCR_EPAR ; 
 int UART_LCR_PARITY ; 
 int /*<<< orphan*/  UART_MCR_DTR ; 
 int /*<<< orphan*/  isdn_tty_modem_hup (TYPE_4__*,int) ; 
 int /*<<< orphan*/  isdn_tty_modem_ncarrier (TYPE_4__*) ; 
 int /*<<< orphan*/  isdn_tty_modem_reset_regs (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_set_check_carrier (struct tty_port*,int) ; 

__attribute__((used)) static void
isdn_tty_change_speed(modem_info *info)
{
	struct tty_port *port = &info->port;
	uint cflag,
		cval,
		quot;
	int i;

	if (!port->tty)
		return;
	cflag = port->tty->termios.c_cflag;

	quot = i = cflag & CBAUD;
	if (i & CBAUDEX) {
		i &= ~CBAUDEX;
		if (i < 1 || i > 2)
			port->tty->termios.c_cflag &= ~CBAUDEX;
		else
			i += 15;
	}
	if (quot) {
		info->mcr |= UART_MCR_DTR;
		isdn_tty_modem_ncarrier(info);
	} else {
		info->mcr &= ~UART_MCR_DTR;
		if (info->emu.mdmreg[REG_DTRHUP] & BIT_DTRHUP) {
#ifdef ISDN_DEBUG_MODEM_HUP
			printk(KERN_DEBUG "Mhup in changespeed\n");
#endif
			if (info->online)
				info->ncarrier = 1;
			isdn_tty_modem_reset_regs(info, 0);
			isdn_tty_modem_hup(info, 1);
		}
		return;
	}
	/* byte size and parity */
	cval = cflag & (CSIZE | CSTOPB);
	cval >>= 4;
	if (cflag & PARENB)
		cval |= UART_LCR_PARITY;
	if (!(cflag & PARODD))
		cval |= UART_LCR_EPAR;

	tty_port_set_check_carrier(port, ~cflag & CLOCAL);
}