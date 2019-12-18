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
struct tty_struct {int dummy; } ;
struct ti_port {scalar_t__ tp_read_urb_state; int /*<<< orphan*/  tp_lock; } ;

/* Variables and functions */
 scalar_t__ TI_READ_URB_RUNNING ; 
 scalar_t__ TI_READ_URB_STOPPING ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ti_stop_read(struct ti_port *tport, struct tty_struct *tty)
{
	unsigned long flags;

	spin_lock_irqsave(&tport->tp_lock, flags);

	if (tport->tp_read_urb_state == TI_READ_URB_RUNNING)
		tport->tp_read_urb_state = TI_READ_URB_STOPPING;

	spin_unlock_irqrestore(&tport->tp_lock, flags);
}