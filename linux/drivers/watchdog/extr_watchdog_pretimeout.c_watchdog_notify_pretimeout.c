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
struct watchdog_device {TYPE_1__* gov; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pretimeout ) (struct watchdog_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pretimeout_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct watchdog_device*) ; 

void watchdog_notify_pretimeout(struct watchdog_device *wdd)
{
	unsigned long flags;

	spin_lock_irqsave(&pretimeout_lock, flags);
	if (!wdd->gov) {
		spin_unlock_irqrestore(&pretimeout_lock, flags);
		return;
	}

	wdd->gov->pretimeout(wdd);
	spin_unlock_irqrestore(&pretimeout_lock, flags);
}