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
struct dpu_power_handle {int /*<<< orphan*/  phandle_lock; } ;
struct dpu_power_event {int /*<<< orphan*/  list; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dpu_power_event*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void dpu_power_handle_unregister_event(
		struct dpu_power_handle *phandle,
		struct dpu_power_event *event)
{
	if (!phandle || !event) {
		pr_err("invalid phandle or event\n");
	} else if (!event->active) {
		pr_err("power handle deinit already done\n");
		kfree(event);
	} else {
		mutex_lock(&phandle->phandle_lock);
		list_del_init(&event->list);
		mutex_unlock(&phandle->phandle_lock);
		kfree(event);
	}
}