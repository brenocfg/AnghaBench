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
struct ps2mult {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ports; int /*<<< orphan*/  mx_serio; } ;

/* Variables and functions */
 size_t PS2MULT_KBD_PORT ; 
 int /*<<< orphan*/  PS2MULT_SESSION_END ; 
 int /*<<< orphan*/  PS2MULT_SESSION_START ; 
 int /*<<< orphan*/  ps2mult_select_port (struct ps2mult*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ps2mult_reset(struct ps2mult *psm)
{
	unsigned long flags;

	spin_lock_irqsave(&psm->lock, flags);

	serio_write(psm->mx_serio, PS2MULT_SESSION_END);
	serio_write(psm->mx_serio, PS2MULT_SESSION_START);

	ps2mult_select_port(psm, &psm->ports[PS2MULT_KBD_PORT]);

	spin_unlock_irqrestore(&psm->lock, flags);
}