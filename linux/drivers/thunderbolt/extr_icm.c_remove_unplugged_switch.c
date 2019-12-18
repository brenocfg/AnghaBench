#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct tb_switch {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  complete_rpm (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_bus_type ; 
 int /*<<< orphan*/  tb_switch_remove (struct tb_switch*) ; 

__attribute__((used)) static void remove_unplugged_switch(struct tb_switch *sw)
{
	pm_runtime_get_sync(sw->dev.parent);

	/*
	 * Signal this and switches below for rpm_complete because
	 * tb_switch_remove() calls pm_runtime_get_sync() that then waits
	 * for it.
	 */
	complete_rpm(&sw->dev, NULL);
	bus_for_each_dev(&tb_bus_type, &sw->dev, NULL, complete_rpm);
	tb_switch_remove(sw);

	pm_runtime_mark_last_busy(sw->dev.parent);
	pm_runtime_put_autosuspend(sw->dev.parent);
}