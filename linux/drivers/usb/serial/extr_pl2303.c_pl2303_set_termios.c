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
typedef  int u8 ;
struct usb_serial_port {int /*<<< orphan*/  dev; struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct ktermios {int c_cflag; } ;
struct tty_struct {struct ktermios termios; } ;
struct pl2303_serial_private {int quirks; int /*<<< orphan*/  type; } ;
struct pl2303_private {int line_control; int /*<<< orphan*/  lock; int /*<<< orphan*/  line_settings; } ;

/* Variables and functions */
 int B0 ; 
 int CBAUD ; 
 int CONTROL_DTR ; 
 int CONTROL_RTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int C_BAUD (struct tty_struct*) ; 
 scalar_t__ C_CMSPAR (struct tty_struct*) ; 
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 int const C_CSIZE (struct tty_struct*) ; 
 scalar_t__ C_CSTOPB (struct tty_struct*) ; 
 scalar_t__ C_PARENB (struct tty_struct*) ; 
 scalar_t__ C_PARODD (struct tty_struct*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PL2303_FLOWCTRL_MASK ; 
 int PL2303_QUIRK_LEGACY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ pl2303_enable_xonxoff (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl2303_encode_baud_rate (struct tty_struct*,struct usb_serial_port*,unsigned char*) ; 
 int /*<<< orphan*/  pl2303_get_line_request (struct usb_serial_port*,unsigned char*) ; 
 int /*<<< orphan*/  pl2303_set_control_lines (struct usb_serial_port*,int) ; 
 int pl2303_set_line_request (struct usb_serial_port*,unsigned char*) ; 
 int /*<<< orphan*/  pl2303_termios_change (struct ktermios*,struct ktermios*) ; 
 int /*<<< orphan*/  pl2303_update_reg (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pl2303_serial_private* usb_get_serial_data (struct usb_serial*) ; 
 struct pl2303_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void pl2303_set_termios(struct tty_struct *tty,
		struct usb_serial_port *port, struct ktermios *old_termios)
{
	struct usb_serial *serial = port->serial;
	struct pl2303_serial_private *spriv = usb_get_serial_data(serial);
	struct pl2303_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;
	unsigned char *buf;
	int ret;
	u8 control;

	if (old_termios && !pl2303_termios_change(&tty->termios, old_termios))
		return;

	buf = kzalloc(7, GFP_KERNEL);
	if (!buf) {
		/* Report back no change occurred */
		if (old_termios)
			tty->termios = *old_termios;
		return;
	}

	pl2303_get_line_request(port, buf);

	switch (C_CSIZE(tty)) {
	case CS5:
		buf[6] = 5;
		break;
	case CS6:
		buf[6] = 6;
		break;
	case CS7:
		buf[6] = 7;
		break;
	default:
	case CS8:
		buf[6] = 8;
	}
	dev_dbg(&port->dev, "data bits = %d\n", buf[6]);

	/* For reference buf[0]:buf[3] baud rate value */
	pl2303_encode_baud_rate(tty, port, &buf[0]);

	/* For reference buf[4]=0 is 1 stop bits */
	/* For reference buf[4]=1 is 1.5 stop bits */
	/* For reference buf[4]=2 is 2 stop bits */
	if (C_CSTOPB(tty)) {
		/*
		 * NOTE: Comply with "real" UARTs / RS232:
		 *       use 1.5 instead of 2 stop bits with 5 data bits
		 */
		if (C_CSIZE(tty) == CS5) {
			buf[4] = 1;
			dev_dbg(&port->dev, "stop bits = 1.5\n");
		} else {
			buf[4] = 2;
			dev_dbg(&port->dev, "stop bits = 2\n");
		}
	} else {
		buf[4] = 0;
		dev_dbg(&port->dev, "stop bits = 1\n");
	}

	if (C_PARENB(tty)) {
		/* For reference buf[5]=0 is none parity */
		/* For reference buf[5]=1 is odd parity */
		/* For reference buf[5]=2 is even parity */
		/* For reference buf[5]=3 is mark parity */
		/* For reference buf[5]=4 is space parity */
		if (C_PARODD(tty)) {
			if (C_CMSPAR(tty)) {
				buf[5] = 3;
				dev_dbg(&port->dev, "parity = mark\n");
			} else {
				buf[5] = 1;
				dev_dbg(&port->dev, "parity = odd\n");
			}
		} else {
			if (C_CMSPAR(tty)) {
				buf[5] = 4;
				dev_dbg(&port->dev, "parity = space\n");
			} else {
				buf[5] = 2;
				dev_dbg(&port->dev, "parity = even\n");
			}
		}
	} else {
		buf[5] = 0;
		dev_dbg(&port->dev, "parity = none\n");
	}

	/*
	 * Some PL2303 are known to lose bytes if you change serial settings
	 * even to the same values as before. Thus we actually need to filter
	 * in this specific case.
	 *
	 * Note that the tty_termios_hw_change check above is not sufficient
	 * as a previously requested baud rate may differ from the one
	 * actually used (and stored in old_termios).
	 *
	 * NOTE: No additional locking needed for line_settings as it is
	 *       only used in set_termios, which is serialised against itself.
	 */
	if (!old_termios || memcmp(buf, priv->line_settings, 7)) {
		ret = pl2303_set_line_request(port, buf);
		if (!ret)
			memcpy(priv->line_settings, buf, 7);
	}

	/* change control lines if we are switching to or from B0 */
	spin_lock_irqsave(&priv->lock, flags);
	control = priv->line_control;
	if (C_BAUD(tty) == B0)
		priv->line_control &= ~(CONTROL_DTR | CONTROL_RTS);
	else if (old_termios && (old_termios->c_cflag & CBAUD) == B0)
		priv->line_control |= (CONTROL_DTR | CONTROL_RTS);
	if (control != priv->line_control) {
		control = priv->line_control;
		spin_unlock_irqrestore(&priv->lock, flags);
		pl2303_set_control_lines(port, control);
	} else {
		spin_unlock_irqrestore(&priv->lock, flags);
	}

	if (C_CRTSCTS(tty)) {
		if (spriv->quirks & PL2303_QUIRK_LEGACY)
			pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0x40);
		else
			pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0x60);
	} else if (pl2303_enable_xonxoff(tty, spriv->type)) {
		pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0xc0);
	} else {
		pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0);
	}

	kfree(buf);
}