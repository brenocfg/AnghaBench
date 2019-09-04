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
struct qib_devdata {TYPE_1__* cspec; } ;
struct TYPE_2__ {int /*<<< orphan*/  relock_timer; scalar_t__ relock_timer_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

void shutdown_7220_relock_poll(struct qib_devdata *dd)
{
	if (dd->cspec->relock_timer_active)
		del_timer_sync(&dd->cspec->relock_timer);
}