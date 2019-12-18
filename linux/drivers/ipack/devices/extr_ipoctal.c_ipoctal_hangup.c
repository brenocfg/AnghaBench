#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct ipoctal_channel* driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  open_wait; } ;
struct ipoctal_channel {TYPE_1__ tty_port; int /*<<< orphan*/  lock; scalar_t__ pointer_write; scalar_t__ pointer_read; scalar_t__ nb_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipoctal_reset_channel (struct ipoctal_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_hangup (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoctal_hangup(struct tty_struct *tty)
{
	unsigned long flags;
	struct ipoctal_channel *channel = tty->driver_data;

	if (channel == NULL)
		return;

	spin_lock_irqsave(&channel->lock, flags);
	channel->nb_bytes = 0;
	channel->pointer_read = 0;
	channel->pointer_write = 0;
	spin_unlock_irqrestore(&channel->lock, flags);

	tty_port_hangup(&channel->tty_port);

	ipoctal_reset_channel(channel);
	tty_port_set_initialized(&channel->tty_port, 0);
	wake_up_interruptible(&channel->tty_port.open_wait);
}