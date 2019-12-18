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
struct applespi_data {int drain; int /*<<< orphan*/  cmd_msg_lock; int /*<<< orphan*/  write_active; int /*<<< orphan*/  drain_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void applespi_drain_writes(struct applespi_data *applespi)
{
	unsigned long flags;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	applespi->drain = true;
	wait_event_lock_irq(applespi->drain_complete, !applespi->write_active,
			    applespi->cmd_msg_lock);

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);
}