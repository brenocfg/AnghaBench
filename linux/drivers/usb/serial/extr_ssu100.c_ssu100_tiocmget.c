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
struct usb_serial_port {TYPE_1__* serial; } ;
struct usb_device {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TIOCM_CAR ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RI ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  UART_MSR ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DSR ; 
 int UART_MSR_RI ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ssu100_getregister (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ssu100_tiocmget(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct usb_device *dev = port->serial->dev;
	u8 *d;
	int r;

	d = kzalloc(2, GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	r = ssu100_getregister(dev, 0, UART_MCR, d);
	if (r < 0)
		goto mget_out;

	r = ssu100_getregister(dev, 0, UART_MSR, d+1);
	if (r < 0)
		goto mget_out;

	r = (d[0] & UART_MCR_DTR ? TIOCM_DTR : 0) |
		(d[0] & UART_MCR_RTS ? TIOCM_RTS : 0) |
		(d[1] & UART_MSR_CTS ? TIOCM_CTS : 0) |
		(d[1] & UART_MSR_DCD ? TIOCM_CAR : 0) |
		(d[1] & UART_MSR_RI ? TIOCM_RI : 0) |
		(d[1] & UART_MSR_DSR ? TIOCM_DSR : 0);

mget_out:
	kfree(d);
	return r;
}