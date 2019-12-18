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
struct tty_struct {int /*<<< orphan*/  port; struct mips_ejtag_fdc_tty_port* driver_data; } ;
struct mips_ejtag_fdc_tty_port {int /*<<< orphan*/  xmit_lock; int /*<<< orphan*/  xmit_empty; scalar_t__ xmit_tail; scalar_t__ xmit_head; scalar_t__ xmit_cnt; struct mips_ejtag_fdc_tty* driver; } ;
struct mips_ejtag_fdc_tty {int /*<<< orphan*/  xmit_total; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_hangup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mips_ejtag_fdc_tty_hangup(struct tty_struct *tty)
{
	struct mips_ejtag_fdc_tty_port *dport = tty->driver_data;
	struct mips_ejtag_fdc_tty *priv = dport->driver;

	/* Drop any data in the xmit buffer */
	spin_lock(&dport->xmit_lock);
	if (dport->xmit_cnt) {
		atomic_sub(dport->xmit_cnt, &priv->xmit_total);
		dport->xmit_cnt = 0;
		dport->xmit_head = 0;
		dport->xmit_tail = 0;
		complete(&dport->xmit_empty);
	}
	spin_unlock(&dport->xmit_lock);

	tty_port_hangup(tty->port);
}