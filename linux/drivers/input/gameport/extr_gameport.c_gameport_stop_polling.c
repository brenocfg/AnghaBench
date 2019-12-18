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
struct gameport {int /*<<< orphan*/  timer_lock; int /*<<< orphan*/  poll_timer; int /*<<< orphan*/  poll_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void gameport_stop_polling(struct gameport *gameport)
{
	spin_lock(&gameport->timer_lock);

	if (!--gameport->poll_cnt)
		del_timer(&gameport->poll_timer);

	spin_unlock(&gameport->timer_lock);
}