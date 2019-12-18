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
struct vcc_port {int dummy; } ;
struct tty_struct {int /*<<< orphan*/  port; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tty_port_hangup (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct vcc_port* vcc_get_ne (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcc_ldc_hup (struct vcc_port*) ; 
 int /*<<< orphan*/  vcc_put (struct vcc_port*,int) ; 

__attribute__((used)) static void vcc_hangup(struct tty_struct *tty)
{
	struct vcc_port *port;

	if (unlikely(!tty)) {
		pr_err("VCC: hangup: Invalid TTY handle\n");
		return;
	}

	port = vcc_get_ne(tty->index);
	if (unlikely(!port)) {
		pr_err("VCC: hangup: Failed to find VCC port\n");
		return;
	}

	if (unlikely(!tty->port)) {
		pr_err("VCC: hangup: TTY port not found\n");
		vcc_put(port, false);
		return;
	}

	vcc_ldc_hup(port);

	vcc_put(port, false);

	tty_port_hangup(tty->port);
}