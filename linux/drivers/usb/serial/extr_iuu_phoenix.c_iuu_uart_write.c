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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {int dummy; } ;
struct tty_struct {int dummy; } ;
struct iuu_private {int /*<<< orphan*/  lock; scalar_t__ writelen; scalar_t__ writebuf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct iuu_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int iuu_uart_write(struct tty_struct *tty, struct usb_serial_port *port,
			  const u8 *buf, int count)
{
	struct iuu_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;

	if (count > 256)
		return -ENOMEM;

	spin_lock_irqsave(&priv->lock, flags);

	/* fill the buffer */
	memcpy(priv->writebuf + priv->writelen, buf, count);
	priv->writelen += count;
	spin_unlock_irqrestore(&priv->lock, flags);

	return count;
}