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
struct cb710_slot {int /*<<< orphan*/  irq_handler; } ;
struct cb710_chip {int /*<<< orphan*/  irq_lock; } ;
typedef  int /*<<< orphan*/  cb710_irq_handler_t ;

/* Variables and functions */
 struct cb710_chip* cb710_slot_to_chip (struct cb710_slot*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cb710_set_irq_handler(struct cb710_slot *slot,
	cb710_irq_handler_t handler)
{
	struct cb710_chip *chip = cb710_slot_to_chip(slot);
	unsigned long flags;

	spin_lock_irqsave(&chip->irq_lock, flags);
	slot->irq_handler = handler;
	spin_unlock_irqrestore(&chip->irq_lock, flags);
}