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
struct usb_serial_port {int /*<<< orphan*/  dev; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct serial_struct {int flags; scalar_t__ custom_divisor; scalar_t__ baud_base; } ;
struct ftdi_private {int flags; scalar_t__ custom_divisor; scalar_t__ baud_base; int /*<<< orphan*/  cfg_lock; } ;

/* Variables and functions */
 int ASYNC_FLAGS ; 
 int ASYNC_SPD_CUST ; 
 int ASYNC_SPD_MASK ; 
 int ASYNC_USR_MASK ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_speed (struct tty_struct*,struct usb_serial_port*) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  write_latency_timer (struct usb_serial_port*) ; 

__attribute__((used)) static int set_serial_info(struct tty_struct *tty,
	struct serial_struct *ss)
{
	struct usb_serial_port *port = tty->driver_data;
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	struct ftdi_private old_priv;

	mutex_lock(&priv->cfg_lock);
	old_priv = *priv;

	/* Do error checking and permission checking */

	if (!capable(CAP_SYS_ADMIN)) {
		if ((ss->flags ^ priv->flags) & ~ASYNC_USR_MASK) {
			mutex_unlock(&priv->cfg_lock);
			return -EPERM;
		}
		priv->flags = ((priv->flags & ~ASYNC_USR_MASK) |
			       (ss->flags & ASYNC_USR_MASK));
		priv->custom_divisor = ss->custom_divisor;
		goto check_and_exit;
	}

	if (ss->baud_base != priv->baud_base) {
		mutex_unlock(&priv->cfg_lock);
		return -EINVAL;
	}

	/* Make the changes - these are privileged changes! */

	priv->flags = ((priv->flags & ~ASYNC_FLAGS) |
					(ss->flags & ASYNC_FLAGS));
	priv->custom_divisor = ss->custom_divisor;

check_and_exit:
	write_latency_timer(port);

	if ((priv->flags ^ old_priv.flags) & ASYNC_SPD_MASK ||
			((priv->flags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST &&
			 priv->custom_divisor != old_priv.custom_divisor)) {

		/* warn about deprecation unless clearing */
		if (priv->flags & ASYNC_SPD_MASK)
			dev_warn_ratelimited(&port->dev, "use of SPD flags is deprecated\n");

		change_speed(tty, port);
	}
	mutex_unlock(&priv->cfg_lock);
	return 0;
}