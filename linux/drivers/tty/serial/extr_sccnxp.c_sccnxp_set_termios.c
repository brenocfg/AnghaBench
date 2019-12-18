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
struct uart_port {int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  dev; } ;
struct sccnxp_port {int /*<<< orphan*/  lock; TYPE_1__* chip; } ;
struct ktermios {int c_cflag; int c_iflag; } ;
struct TYPE_2__ {long flags; } ;

/* Variables and functions */
 int BRKINT ; 
 int CMSPAR ; 
 int CREAD ; 
 int CR_CMD_BREAK_RESET ; 
 int CR_CMD_MRPTR1 ; 
 int CR_CMD_RX_RESET ; 
 int CR_CMD_STATUS_RESET ; 
 int CR_CMD_TX_RESET ; 
 int CR_RX_DISABLE ; 
 int CR_RX_ENABLE ; 
 int CR_TX_DISABLE ; 
 int CR_TX_ENABLE ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int MR1_BITS_5 ; 
 int MR1_BITS_6 ; 
 int MR1_BITS_7 ; 
 int MR1_BITS_8 ; 
 int MR1_PAR_NO ; 
 int MR1_PAR_ODD ; 
 int MR2_STOP1 ; 
 int MR2_STOP2 ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int /*<<< orphan*/  SCCNXP_CR_REG ; 
 long SCCNXP_HAVE_MR0 ; 
 int /*<<< orphan*/  SCCNXP_MR_REG ; 
 int SR_BRK ; 
 int SR_FE ; 
 int SR_OVR ; 
 int SR_PE ; 
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_port_write (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int sccnxp_set_baud (struct uart_port*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,int,int) ; 
 int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,int) ; 

__attribute__((used)) static void sccnxp_set_termios(struct uart_port *port,
			       struct ktermios *termios, struct ktermios *old)
{
	struct sccnxp_port *s = dev_get_drvdata(port->dev);
	unsigned long flags;
	u8 mr1, mr2;
	int baud;

	spin_lock_irqsave(&s->lock, flags);

	/* Mask termios capabilities we don't support */
	termios->c_cflag &= ~CMSPAR;

	/* Disable RX & TX, reset break condition, status and FIFOs */
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_RX_RESET |
					       CR_RX_DISABLE | CR_TX_DISABLE);
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_TX_RESET);
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_STATUS_RESET);
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_BREAK_RESET);

	/* Word size */
	switch (termios->c_cflag & CSIZE) {
	case CS5:
		mr1 = MR1_BITS_5;
		break;
	case CS6:
		mr1 = MR1_BITS_6;
		break;
	case CS7:
		mr1 = MR1_BITS_7;
		break;
	case CS8:
	default:
		mr1 = MR1_BITS_8;
		break;
	}

	/* Parity */
	if (termios->c_cflag & PARENB) {
		if (termios->c_cflag & PARODD)
			mr1 |= MR1_PAR_ODD;
	} else
		mr1 |= MR1_PAR_NO;

	/* Stop bits */
	mr2 = (termios->c_cflag & CSTOPB) ? MR2_STOP2 : MR2_STOP1;

	/* Update desired format */
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_MRPTR1);
	sccnxp_port_write(port, SCCNXP_MR_REG, mr1);
	sccnxp_port_write(port, SCCNXP_MR_REG, mr2);

	/* Set read status mask */
	port->read_status_mask = SR_OVR;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= SR_PE | SR_FE;
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		port->read_status_mask |= SR_BRK;

	/* Set status ignore mask */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNBRK)
		port->ignore_status_mask |= SR_BRK;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= SR_PE;
	if (!(termios->c_cflag & CREAD))
		port->ignore_status_mask |= SR_PE | SR_OVR | SR_FE | SR_BRK;

	/* Setup baudrate */
	baud = uart_get_baud_rate(port, termios, old, 50,
				  (s->chip->flags & SCCNXP_HAVE_MR0) ?
				  230400 : 38400);
	baud = sccnxp_set_baud(port, baud);

	/* Update timeout according to new baud rate */
	uart_update_timeout(port, termios->c_cflag, baud);

	/* Report actual baudrate back to core */
	if (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

	/* Enable RX & TX */
	sccnxp_port_write(port, SCCNXP_CR_REG, CR_RX_ENABLE | CR_TX_ENABLE);

	spin_unlock_irqrestore(&s->lock, flags);
}