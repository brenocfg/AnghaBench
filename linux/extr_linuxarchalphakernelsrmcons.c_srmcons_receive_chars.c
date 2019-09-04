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
struct tty_port {int /*<<< orphan*/  lock; scalar_t__ tty; } ;
struct timer_list {int dummy; } ;
struct srmcons_private {int /*<<< orphan*/  timer; struct tty_port port; } ;

/* Variables and functions */
 struct srmcons_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srmcons_callback_lock ; 
 int /*<<< orphan*/  srmcons_do_receive_chars (struct tty_port*) ; 
 struct srmcons_private* srmconsp ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void
srmcons_receive_chars(struct timer_list *t)
{
	struct srmcons_private *srmconsp = from_timer(srmconsp, t, timer);
	struct tty_port *port = &srmconsp->port;
	unsigned long flags;
	int incr = 10;

	local_irq_save(flags);
	if (spin_trylock(&srmcons_callback_lock)) {
		if (!srmcons_do_receive_chars(port))
			incr = 100;
		spin_unlock(&srmcons_callback_lock);
	} 

	spin_lock(&port->lock);
	if (port->tty)
		mod_timer(&srmconsp->timer, jiffies + incr);
	spin_unlock(&port->lock);

	local_irq_restore(flags);
}