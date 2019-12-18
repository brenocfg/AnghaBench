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
struct TYPE_6__ {unsigned int c_cflag; } ;
struct tty_struct {TYPE_3__ termios; struct ipoctal_channel* driver_data; } ;
struct ktermios {int dummy; } ;
struct ipoctal_channel {int board_id; TYPE_2__* regs; scalar_t__ rx_enable; } ;
typedef  int speed_t ;
struct TYPE_4__ {int /*<<< orphan*/  cr; int /*<<< orphan*/  csr; int /*<<< orphan*/  mr; } ;
struct TYPE_5__ {TYPE_1__ w; } ;

/* Variables and functions */
 unsigned int CMSPAR ; 
 unsigned int CRTSCTS ; 
 unsigned char CR_ENABLE_RX ; 
#define  CS6 133 
#define  CS7 132 
#define  CS8 131 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
#define  IPACK1_DEVICE_ID_SBS_OCTAL_232 130 
#define  IPACK1_DEVICE_ID_SBS_OCTAL_422 129 
#define  IPACK1_DEVICE_ID_SBS_OCTAL_485 128 
 unsigned char MR1_CHRL_6_BITS ; 
 unsigned char MR1_CHRL_7_BITS ; 
 unsigned char MR1_CHRL_8_BITS ; 
 unsigned char MR1_ERROR_CHAR ; 
 unsigned char MR1_PARITY_EVEN ; 
 unsigned char MR1_PARITY_ODD ; 
 unsigned char MR1_PARITY_OFF ; 
 unsigned char MR1_PARITY_ON ; 
 unsigned char MR1_RxINT_RxRDY ; 
 unsigned char MR1_RxRTS_CONTROL_OFF ; 
 unsigned char MR1_RxRTS_CONTROL_ON ; 
 unsigned char MR2_CTS_ENABLE_TX_OFF ; 
 unsigned char MR2_CTS_ENABLE_TX_ON ; 
 unsigned char MR2_STOP_BITS_LENGTH_1 ; 
 unsigned char MR2_STOP_BITS_LENGTH_2 ; 
 unsigned char MR2_TxRTS_CONTROL_OFF ; 
 unsigned char MR2_TxRTS_CONTROL_ON ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 unsigned char RX_CLK_110 ; 
 unsigned char RX_CLK_1200 ; 
 unsigned char RX_CLK_150 ; 
 unsigned char RX_CLK_1800 ; 
 unsigned char RX_CLK_19200 ; 
 unsigned char RX_CLK_2000 ; 
 unsigned char RX_CLK_2400 ; 
 unsigned char RX_CLK_300 ; 
 unsigned char RX_CLK_38400 ; 
 unsigned char RX_CLK_4800 ; 
 unsigned char RX_CLK_600 ; 
 unsigned char RX_CLK_75 ; 
 unsigned char RX_CLK_9600 ; 
 unsigned char TX_CLK_110 ; 
 unsigned char TX_CLK_1200 ; 
 unsigned char TX_CLK_150 ; 
 unsigned char TX_CLK_1800 ; 
 unsigned char TX_CLK_19200 ; 
 unsigned char TX_CLK_2000 ; 
 unsigned char TX_CLK_2400 ; 
 unsigned char TX_CLK_300 ; 
 unsigned char TX_CLK_38400 ; 
 unsigned char TX_CLK_4800 ; 
 unsigned char TX_CLK_600 ; 
 unsigned char TX_CLK_75 ; 
 unsigned char TX_CLK_9600 ; 
 int /*<<< orphan*/  iowrite8 (unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoctal_reset_channel (struct ipoctal_channel*) ; 
 int tty_get_baud_rate (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (TYPE_3__*,int,int) ; 

__attribute__((used)) static void ipoctal_set_termios(struct tty_struct *tty,
				struct ktermios *old_termios)
{
	unsigned int cflag;
	unsigned char mr1 = 0;
	unsigned char mr2 = 0;
	unsigned char csr = 0;
	struct ipoctal_channel *channel = tty->driver_data;
	speed_t baud;

	cflag = tty->termios.c_cflag;

	/* Disable and reset everything before change the setup */
	ipoctal_reset_channel(channel);

	/* Set Bits per chars */
	switch (cflag & CSIZE) {
	case CS6:
		mr1 |= MR1_CHRL_6_BITS;
		break;
	case CS7:
		mr1 |= MR1_CHRL_7_BITS;
		break;
	case CS8:
	default:
		mr1 |= MR1_CHRL_8_BITS;
		/* By default, select CS8 */
		tty->termios.c_cflag = (cflag & ~CSIZE) | CS8;
		break;
	}

	/* Set Parity */
	if (cflag & PARENB)
		if (cflag & PARODD)
			mr1 |= MR1_PARITY_ON | MR1_PARITY_ODD;
		else
			mr1 |= MR1_PARITY_ON | MR1_PARITY_EVEN;
	else
		mr1 |= MR1_PARITY_OFF;

	/* Mark or space parity is not supported */
	tty->termios.c_cflag &= ~CMSPAR;

	/* Set stop bits */
	if (cflag & CSTOPB)
		mr2 |= MR2_STOP_BITS_LENGTH_2;
	else
		mr2 |= MR2_STOP_BITS_LENGTH_1;

	/* Set the flow control */
	switch (channel->board_id) {
	case IPACK1_DEVICE_ID_SBS_OCTAL_232:
		if (cflag & CRTSCTS) {
			mr1 |= MR1_RxRTS_CONTROL_ON;
			mr2 |= MR2_TxRTS_CONTROL_OFF | MR2_CTS_ENABLE_TX_ON;
		} else {
			mr1 |= MR1_RxRTS_CONTROL_OFF;
			mr2 |= MR2_TxRTS_CONTROL_OFF | MR2_CTS_ENABLE_TX_OFF;
		}
		break;
	case IPACK1_DEVICE_ID_SBS_OCTAL_422:
		mr1 |= MR1_RxRTS_CONTROL_OFF;
		mr2 |= MR2_TxRTS_CONTROL_OFF | MR2_CTS_ENABLE_TX_OFF;
		break;
	case IPACK1_DEVICE_ID_SBS_OCTAL_485:
		mr1 |= MR1_RxRTS_CONTROL_OFF;
		mr2 |= MR2_TxRTS_CONTROL_ON | MR2_CTS_ENABLE_TX_OFF;
		break;
	default:
		return;
		break;
	}

	baud = tty_get_baud_rate(tty);
	tty_termios_encode_baud_rate(&tty->termios, baud, baud);

	/* Set baud rate */
	switch (baud) {
	case 75:
		csr |= TX_CLK_75 | RX_CLK_75;
		break;
	case 110:
		csr |= TX_CLK_110 | RX_CLK_110;
		break;
	case 150:
		csr |= TX_CLK_150 | RX_CLK_150;
		break;
	case 300:
		csr |= TX_CLK_300 | RX_CLK_300;
		break;
	case 600:
		csr |= TX_CLK_600 | RX_CLK_600;
		break;
	case 1200:
		csr |= TX_CLK_1200 | RX_CLK_1200;
		break;
	case 1800:
		csr |= TX_CLK_1800 | RX_CLK_1800;
		break;
	case 2000:
		csr |= TX_CLK_2000 | RX_CLK_2000;
		break;
	case 2400:
		csr |= TX_CLK_2400 | RX_CLK_2400;
		break;
	case 4800:
		csr |= TX_CLK_4800  | RX_CLK_4800;
		break;
	case 9600:
		csr |= TX_CLK_9600  | RX_CLK_9600;
		break;
	case 19200:
		csr |= TX_CLK_19200 | RX_CLK_19200;
		break;
	case 38400:
	default:
		csr |= TX_CLK_38400 | RX_CLK_38400;
		/* In case of default, we establish 38400 bps */
		tty_termios_encode_baud_rate(&tty->termios, 38400, 38400);
		break;
	}

	mr1 |= MR1_ERROR_CHAR;
	mr1 |= MR1_RxINT_RxRDY;

	/* Write the control registers */
	iowrite8(mr1, &channel->regs->w.mr);
	iowrite8(mr2, &channel->regs->w.mr);
	iowrite8(csr, &channel->regs->w.csr);

	/* Enable again the RX, if it was before */
	if (channel->rx_enable)
		iowrite8(CR_ENABLE_RX, &channel->regs->w.cr);
}