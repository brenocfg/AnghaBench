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
struct hvsi_priv {TYPE_2__* tty; scalar_t__ opened; int /*<<< orphan*/  termno; int /*<<< orphan*/  is_console; } ;
struct hvc_struct {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int c_cflag; } ;
struct TYPE_4__ {TYPE_1__ termios; } ;

/* Variables and functions */
 int HUPCL ; 
 int /*<<< orphan*/  hvsi_send_close (struct hvsi_priv*) ; 
 int /*<<< orphan*/  hvsilib_write_mctrl (struct hvsi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_kref_put (TYPE_2__*) ; 

void hvsilib_close(struct hvsi_priv *pv, struct hvc_struct *hp)
{
	unsigned long flags;

	pr_devel("HVSI@%x: close !\n", pv->termno);

	if (!pv->is_console) {
		pr_devel("HVSI@%x: Not a console, tearing down\n",
			 pv->termno);

		/* Clear opened, synchronize with khvcd */
		spin_lock_irqsave(&hp->lock, flags);
		pv->opened = 0;
		spin_unlock_irqrestore(&hp->lock, flags);

		/* Clear our own DTR */
		if (!pv->tty || (pv->tty->termios.c_cflag & HUPCL))
			hvsilib_write_mctrl(pv, 0);

		/* Tear down the connection */
		hvsi_send_close(pv);
	}

	tty_kref_put(pv->tty);
	pv->tty = NULL;
}