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
struct vcc_port {struct tty_struct* tty; } ;
struct tty_struct {scalar_t__ index; struct tty_port* port; } ;
struct tty_port {int /*<<< orphan*/ * ops; } ;
struct tty_driver {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VCC_MAX_PORTS ; 
 int /*<<< orphan*/  kfree (struct tty_port*) ; 
 struct tty_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tty_port_init (struct tty_port*) ; 
 int tty_standard_install (struct tty_driver*,struct tty_struct*) ; 
 scalar_t__ unlikely (int) ; 
 struct vcc_port* vcc_get (scalar_t__,int) ; 
 int /*<<< orphan*/  vcc_port_ops ; 
 int /*<<< orphan*/  vcc_put (struct vcc_port*,int) ; 

__attribute__((used)) static int vcc_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct vcc_port *port_vcc;
	struct tty_port *port_tty;
	int ret;

	if (unlikely(!tty)) {
		pr_err("VCC: install: Invalid TTY handle\n");
		return -ENXIO;
	}

	if (tty->index >= VCC_MAX_PORTS)
		return -EINVAL;

	ret = tty_standard_install(driver, tty);
	if (ret)
		return ret;

	port_tty = kzalloc(sizeof(struct tty_port), GFP_KERNEL);
	if (!port_tty)
		return -ENOMEM;

	port_vcc = vcc_get(tty->index, true);
	if (!port_vcc) {
		pr_err("VCC: install: Failed to find VCC port\n");
		tty->port = NULL;
		kfree(port_tty);
		return -ENODEV;
	}

	tty_port_init(port_tty);
	port_tty->ops = &vcc_port_ops;
	tty->port = port_tty;

	port_vcc->tty = tty;

	vcc_put(port_vcc, true);

	return 0;
}