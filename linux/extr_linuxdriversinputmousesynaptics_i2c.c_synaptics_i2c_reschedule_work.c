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
struct synaptics_i2c {int /*<<< orphan*/  lock; int /*<<< orphan*/  dwork; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void synaptics_i2c_reschedule_work(struct synaptics_i2c *touch,
					  unsigned long delay)
{
	unsigned long flags;

	spin_lock_irqsave(&touch->lock, flags);

	mod_delayed_work(system_wq, &touch->dwork, delay);

	spin_unlock_irqrestore(&touch->lock, flags);
}