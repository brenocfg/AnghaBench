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
struct gameport {int /*<<< orphan*/  timer_lock; int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  poll_timer; int /*<<< orphan*/  poll_handler; int /*<<< orphan*/  poll_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void gameport_start_polling(struct gameport *gameport)
{
	spin_lock(&gameport->timer_lock);

	if (!gameport->poll_cnt++) {
		BUG_ON(!gameport->poll_handler);
		BUG_ON(!gameport->poll_interval);
		mod_timer(&gameport->poll_timer, jiffies + msecs_to_jiffies(gameport->poll_interval));
	}

	spin_unlock(&gameport->timer_lock);
}