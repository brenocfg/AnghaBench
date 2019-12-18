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
struct vcc_port {int /*<<< orphan*/  lock; } ;
struct tty_struct {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  VCC_CTL_BREAK ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 struct vcc_port* vcc_get_ne (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcc_kick_tx (struct vcc_port*) ; 
 int /*<<< orphan*/  vcc_put (struct vcc_port*,int) ; 
 scalar_t__ vcc_send_ctl (struct vcc_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vcc_break_ctl(struct tty_struct *tty, int state)
{
	struct vcc_port *port;
	unsigned long flags;

	if (unlikely(!tty)) {
		pr_err("VCC: break_ctl: Invalid TTY handle\n");
		return -ENXIO;
	}

	port = vcc_get_ne(tty->index);
	if (unlikely(!port)) {
		pr_err("VCC: break_ctl: Failed to find VCC port\n");
		return -ENODEV;
	}

	/* Turn off break */
	if (state == 0) {
		vcc_put(port, false);
		return 0;
	}

	spin_lock_irqsave(&port->lock, flags);

	if (vcc_send_ctl(port, VCC_CTL_BREAK) < 0)
		vcc_kick_tx(port);

	spin_unlock_irqrestore(&port->lock, flags);

	vcc_put(port, false);

	return 0;
}