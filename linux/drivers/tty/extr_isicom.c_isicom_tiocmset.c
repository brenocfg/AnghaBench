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
struct tty_struct {int /*<<< orphan*/  name; struct isi_port* driver_data; } ;
struct isi_port {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  drop_dtr (struct isi_port*) ; 
 int /*<<< orphan*/  drop_rts (struct isi_port*) ; 
 scalar_t__ isicom_paranoia_check (struct isi_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  raise_dtr (struct isi_port*) ; 
 int /*<<< orphan*/  raise_rts (struct isi_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int isicom_tiocmset(struct tty_struct *tty,
					unsigned int set, unsigned int clear)
{
	struct isi_port *port = tty->driver_data;
	unsigned long flags;

	if (isicom_paranoia_check(port, tty->name, "isicom_ioctl"))
		return -ENODEV;

	spin_lock_irqsave(&port->card->card_lock, flags);
	if (set & TIOCM_RTS)
		raise_rts(port);
	if (set & TIOCM_DTR)
		raise_dtr(port);

	if (clear & TIOCM_RTS)
		drop_rts(port);
	if (clear & TIOCM_DTR)
		drop_dtr(port);
	spin_unlock_irqrestore(&port->card->card_lock, flags);

	return 0;
}