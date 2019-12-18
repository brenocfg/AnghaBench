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
struct usb_serial_port {TYPE_1__* serial; } ;
struct TYPE_4__ {int c_cflag; } ;
struct tty_struct {TYPE_2__ termios; } ;
struct ktermios {int dummy; } ;
struct kobil_private {scalar_t__ device_type; } ;
typedef  int speed_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CMSPAR ; 
 int CSTOPB ; 
 scalar_t__ KOBIL_KAAN_SIM_PRODUCT_ID ; 
 int /*<<< orphan*/  KOBIL_TIMEOUT ; 
 scalar_t__ KOBIL_USBTWIN_PRODUCT_ID ; 
 int PARENB ; 
 int PARODD ; 
 unsigned short SUSBCR_SBR_1200 ; 
 unsigned short SUSBCR_SBR_9600 ; 
 unsigned short SUSBCR_SPASB_1StopBit ; 
 unsigned short SUSBCR_SPASB_2StopBits ; 
 unsigned short SUSBCR_SPASB_EvenParity ; 
 unsigned short SUSBCR_SPASB_NoParity ; 
 unsigned short SUSBCR_SPASB_OddParity ; 
 int /*<<< orphan*/  SUSBCRequest_SetBaudRateParityAndStopBits ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  tty_encode_baud_rate (struct tty_struct*,int,int) ; 
 int tty_get_baud_rate (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_termios_copy_hw (TYPE_2__*,struct ktermios*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kobil_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kobil_set_termios(struct tty_struct *tty,
			struct usb_serial_port *port, struct ktermios *old)
{
	struct kobil_private *priv;
	int result;
	unsigned short urb_val = 0;
	int c_cflag = tty->termios.c_cflag;
	speed_t speed;

	priv = usb_get_serial_port_data(port);
	if (priv->device_type == KOBIL_USBTWIN_PRODUCT_ID ||
			priv->device_type == KOBIL_KAAN_SIM_PRODUCT_ID) {
		/* This device doesn't support ioctl calls */
		tty_termios_copy_hw(&tty->termios, old);
		return;
	}

	speed = tty_get_baud_rate(tty);
	switch (speed) {
	case 1200:
		urb_val = SUSBCR_SBR_1200;
		break;
	default:
		speed = 9600;
		/* fall through */
	case 9600:
		urb_val = SUSBCR_SBR_9600;
		break;
	}
	urb_val |= (c_cflag & CSTOPB) ? SUSBCR_SPASB_2StopBits :
							SUSBCR_SPASB_1StopBit;
	if (c_cflag & PARENB) {
		if  (c_cflag & PARODD)
			urb_val |= SUSBCR_SPASB_OddParity;
		else
			urb_val |= SUSBCR_SPASB_EvenParity;
	} else
		urb_val |= SUSBCR_SPASB_NoParity;
	tty->termios.c_cflag &= ~CMSPAR;
	tty_encode_baud_rate(tty, speed, speed);

	result = usb_control_msg(port->serial->dev,
		  usb_sndctrlpipe(port->serial->dev, 0),
		  SUSBCRequest_SetBaudRateParityAndStopBits,
		  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_DIR_OUT,
		  urb_val,
		  0,
		  NULL,
		  0,
		  KOBIL_TIMEOUT
		);
}