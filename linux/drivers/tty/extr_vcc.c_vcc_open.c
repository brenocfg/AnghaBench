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
struct TYPE_3__ {int /*<<< orphan*/  lp; } ;
struct vcc_port {TYPE_1__ vio; } ;
struct tty_struct {int count; TYPE_2__* port; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENXIO ; 
 int EPIPE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int tty_port_open (TYPE_2__*,struct tty_struct*,struct file*) ; 
 scalar_t__ unlikely (int) ; 
 struct vcc_port* vcc_get_ne (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcc_put (struct vcc_port*,int) ; 
 int /*<<< orphan*/  vccdbgl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vcc_open(struct tty_struct *tty, struct file *vcc_file)
{
	struct vcc_port *port;

	if (unlikely(!tty)) {
		pr_err("VCC: open: Invalid TTY handle\n");
		return -ENXIO;
	}

	if (tty->count > 1)
		return -EBUSY;

	port = vcc_get_ne(tty->index);
	if (unlikely(!port)) {
		pr_err("VCC: open: Failed to find VCC port\n");
		return -ENODEV;
	}

	if (unlikely(!port->vio.lp)) {
		pr_err("VCC: open: LDC channel not configured\n");
		vcc_put(port, false);
		return -EPIPE;
	}
	vccdbgl(port->vio.lp);

	vcc_put(port, false);

	if (unlikely(!tty->port)) {
		pr_err("VCC: open: TTY port not found\n");
		return -ENXIO;
	}

	if (unlikely(!tty->port->ops)) {
		pr_err("VCC: open: TTY ops not defined\n");
		return -ENXIO;
	}

	return tty_port_open(tty->port, tty, vcc_file);
}