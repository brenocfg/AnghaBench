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
struct serio {struct ps2mult_port* port_data; int /*<<< orphan*/  parent; } ;
struct ps2mult_port {int registered; } ;
struct ps2mult {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct ps2mult* serio_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ps2mult_serio_stop(struct serio *serio)
{
	struct ps2mult *psm = serio_get_drvdata(serio->parent);
	struct ps2mult_port *port = serio->port_data;
	unsigned long flags;

	spin_lock_irqsave(&psm->lock, flags);
	port->registered = false;
	spin_unlock_irqrestore(&psm->lock, flags);
}