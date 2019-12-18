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
struct watchdog_device {int /*<<< orphan*/  id; int /*<<< orphan*/  restart_nb; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ restart; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_restart_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_dev_unregister (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_ida ; 

__attribute__((used)) static void __watchdog_unregister_device(struct watchdog_device *wdd)
{
	if (wdd == NULL)
		return;

	if (wdd->ops->restart)
		unregister_restart_handler(&wdd->restart_nb);

	watchdog_dev_unregister(wdd);
	ida_simple_remove(&watchdog_ida, wdd->id);
}