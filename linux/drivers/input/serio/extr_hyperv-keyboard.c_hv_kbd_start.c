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
struct serio {struct hv_kbd_dev* port_data; } ;
struct hv_kbd_dev {int started; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hv_kbd_start(struct serio *serio)
{
	struct hv_kbd_dev *kbd_dev = serio->port_data;
	unsigned long flags;

	spin_lock_irqsave(&kbd_dev->lock, flags);
	kbd_dev->started = true;
	spin_unlock_irqrestore(&kbd_dev->lock, flags);

	return 0;
}