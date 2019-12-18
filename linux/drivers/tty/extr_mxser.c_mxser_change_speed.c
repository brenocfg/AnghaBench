#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int c_cflag; } ;
struct tty_struct {size_t index; int hw_stopped; TYPE_1__ termios; struct mxser_port* driver_data; } ;
struct mxser_port {scalar_t__ type; int rx_trigger; unsigned int IER; unsigned int MCR; int read_status_mask; int ignore_status_mask; scalar_t__ ioaddr; TYPE_2__* board; int /*<<< orphan*/  port; } ;
struct TYPE_4__ {scalar_t__ chip_flag; } ;

/* Variables and functions */
 unsigned int CLOCAL ; 
 unsigned int CMSPAR ; 
 unsigned int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 scalar_t__ I_BRKINT (struct tty_struct*) ; 
 scalar_t__ I_IGNBRK (struct tty_struct*) ; 
 scalar_t__ I_IGNPAR (struct tty_struct*) ; 
 scalar_t__ I_INPCK (struct tty_struct*) ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 unsigned int MOXA_MUST_FCR_GDA_MODE_ENABLE ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 scalar_t__ PORT_16450 ; 
 scalar_t__ PORT_16550A ; 
 scalar_t__ PORT_8250 ; 
 int /*<<< orphan*/  START_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 scalar_t__ UART_FCR ; 
 unsigned int UART_FCR_ENABLE_FIFO ; 
 unsigned int UART_FCR_TRIGGER_1 ; 
 unsigned int UART_FCR_TRIGGER_14 ; 
 unsigned int UART_FCR_TRIGGER_4 ; 
 unsigned int UART_FCR_TRIGGER_8 ; 
 scalar_t__ UART_IER ; 
 unsigned int UART_IER_MSI ; 
 unsigned int UART_IER_THRI ; 
 scalar_t__ UART_LCR ; 
 unsigned int UART_LCR_EPAR ; 
 unsigned int UART_LCR_PARITY ; 
 unsigned int UART_LCR_SPAR ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int UART_LSR_THRE ; 
 scalar_t__ UART_MCR ; 
 unsigned int UART_MCR_AFE ; 
 scalar_t__ UART_MSR ; 
 unsigned char UART_MSR_CTS ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  mxser_disable_must_rx_software_flow_control (scalar_t__) ; 
 int /*<<< orphan*/  mxser_disable_must_tx_software_flow_control (scalar_t__) ; 
 int /*<<< orphan*/  mxser_enable_must_rx_software_flow_control (scalar_t__) ; 
 int /*<<< orphan*/  mxser_enable_must_tx_software_flow_control (scalar_t__) ; 
 int /*<<< orphan*/  mxser_set_baud (struct tty_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__* mxser_set_baud_method ; 
 int /*<<< orphan*/  mxser_set_must_fifo_value (struct mxser_port*) ; 
 int /*<<< orphan*/  mxser_set_must_xoff1_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxser_set_must_xon1_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  tty_get_baud_rate (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_set_check_carrier (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tty_port_set_cts_flow (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static int mxser_change_speed(struct tty_struct *tty)
{
	struct mxser_port *info = tty->driver_data;
	unsigned cflag, cval, fcr;
	int ret = 0;
	unsigned char status;

	cflag = tty->termios.c_cflag;
	if (!info->ioaddr)
		return ret;

	if (mxser_set_baud_method[tty->index] == 0)
		mxser_set_baud(tty, tty_get_baud_rate(tty));

	/* byte size and parity */
	switch (cflag & CSIZE) {
	case CS5:
		cval = 0x00;
		break;
	case CS6:
		cval = 0x01;
		break;
	case CS7:
		cval = 0x02;
		break;
	case CS8:
		cval = 0x03;
		break;
	default:
		cval = 0x00;
		break;		/* too keep GCC shut... */
	}
	if (cflag & CSTOPB)
		cval |= 0x04;
	if (cflag & PARENB)
		cval |= UART_LCR_PARITY;
	if (!(cflag & PARODD))
		cval |= UART_LCR_EPAR;
	if (cflag & CMSPAR)
		cval |= UART_LCR_SPAR;

	if ((info->type == PORT_8250) || (info->type == PORT_16450)) {
		if (info->board->chip_flag) {
			fcr = UART_FCR_ENABLE_FIFO;
			fcr |= MOXA_MUST_FCR_GDA_MODE_ENABLE;
			mxser_set_must_fifo_value(info);
		} else
			fcr = 0;
	} else {
		fcr = UART_FCR_ENABLE_FIFO;
		if (info->board->chip_flag) {
			fcr |= MOXA_MUST_FCR_GDA_MODE_ENABLE;
			mxser_set_must_fifo_value(info);
		} else {
			switch (info->rx_trigger) {
			case 1:
				fcr |= UART_FCR_TRIGGER_1;
				break;
			case 4:
				fcr |= UART_FCR_TRIGGER_4;
				break;
			case 8:
				fcr |= UART_FCR_TRIGGER_8;
				break;
			default:
				fcr |= UART_FCR_TRIGGER_14;
				break;
			}
		}
	}

	/* CTS flow control flag and modem status interrupts */
	info->IER &= ~UART_IER_MSI;
	info->MCR &= ~UART_MCR_AFE;
	tty_port_set_cts_flow(&info->port, cflag & CRTSCTS);
	if (cflag & CRTSCTS) {
		info->IER |= UART_IER_MSI;
		if ((info->type == PORT_16550A) || (info->board->chip_flag)) {
			info->MCR |= UART_MCR_AFE;
		} else {
			status = inb(info->ioaddr + UART_MSR);
			if (tty->hw_stopped) {
				if (status & UART_MSR_CTS) {
					tty->hw_stopped = 0;
					if (info->type != PORT_16550A &&
							!info->board->chip_flag) {
						outb(info->IER & ~UART_IER_THRI,
							info->ioaddr +
							UART_IER);
						info->IER |= UART_IER_THRI;
						outb(info->IER, info->ioaddr +
								UART_IER);
					}
					tty_wakeup(tty);
				}
			} else {
				if (!(status & UART_MSR_CTS)) {
					tty->hw_stopped = 1;
					if ((info->type != PORT_16550A) &&
							(!info->board->chip_flag)) {
						info->IER &= ~UART_IER_THRI;
						outb(info->IER, info->ioaddr +
								UART_IER);
					}
				}
			}
		}
	}
	outb(info->MCR, info->ioaddr + UART_MCR);
	tty_port_set_check_carrier(&info->port, ~cflag & CLOCAL);
	if (~cflag & CLOCAL)
		info->IER |= UART_IER_MSI;
	outb(info->IER, info->ioaddr + UART_IER);

	/*
	 * Set up parity check flag
	 */
	info->read_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	if (I_INPCK(tty))
		info->read_status_mask |= UART_LSR_FE | UART_LSR_PE;
	if (I_BRKINT(tty) || I_PARMRK(tty))
		info->read_status_mask |= UART_LSR_BI;

	info->ignore_status_mask = 0;

	if (I_IGNBRK(tty)) {
		info->ignore_status_mask |= UART_LSR_BI;
		info->read_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignore parity and break indicators, ignore
		 * overruns too.  (For real raw support).
		 */
		if (I_IGNPAR(tty)) {
			info->ignore_status_mask |=
						UART_LSR_OE |
						UART_LSR_PE |
						UART_LSR_FE;
			info->read_status_mask |=
						UART_LSR_OE |
						UART_LSR_PE |
						UART_LSR_FE;
		}
	}
	if (info->board->chip_flag) {
		mxser_set_must_xon1_value(info->ioaddr, START_CHAR(tty));
		mxser_set_must_xoff1_value(info->ioaddr, STOP_CHAR(tty));
		if (I_IXON(tty)) {
			mxser_enable_must_rx_software_flow_control(
					info->ioaddr);
		} else {
			mxser_disable_must_rx_software_flow_control(
					info->ioaddr);
		}
		if (I_IXOFF(tty)) {
			mxser_enable_must_tx_software_flow_control(
					info->ioaddr);
		} else {
			mxser_disable_must_tx_software_flow_control(
					info->ioaddr);
		}
	}


	outb(fcr, info->ioaddr + UART_FCR);	/* set fcr */
	outb(cval, info->ioaddr + UART_LCR);

	return ret;
}