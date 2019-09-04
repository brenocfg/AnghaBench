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
struct io_tracker {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __iot_idle_for (struct io_tracker*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool iot_idle_for(struct io_tracker *iot, unsigned long jifs)
{
	bool r;
	unsigned long flags;

	spin_lock_irqsave(&iot->lock, flags);
	r = __iot_idle_for(iot, jifs);
	spin_unlock_irqrestore(&iot->lock, flags);

	return r;
}