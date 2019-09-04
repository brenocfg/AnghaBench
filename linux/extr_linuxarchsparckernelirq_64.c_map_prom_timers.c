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
struct sun5_timer {int dummy; } ;
struct device_node {struct device_node* sibling; int /*<<< orphan*/  name; struct device_node* child; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_path (char*) ; 
 unsigned int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prom_printf (char*) ; 
 struct sun5_timer* prom_timers ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void map_prom_timers(void)
{
	struct device_node *dp;
	const unsigned int *addr;

	/* PROM timer node hangs out in the top level of device siblings... */
	dp = of_find_node_by_path("/");
	dp = dp->child;
	while (dp) {
		if (!strcmp(dp->name, "counter-timer"))
			break;
		dp = dp->sibling;
	}

	/* Assume if node is not present, PROM uses different tick mechanism
	 * which we should not care about.
	 */
	if (!dp) {
		prom_timers = (struct sun5_timer *) 0;
		return;
	}

	/* If PROM is really using this, it must be mapped by him. */
	addr = of_get_property(dp, "address", NULL);
	if (!addr) {
		prom_printf("PROM does not have timer mapped, trying to continue.\n");
		prom_timers = (struct sun5_timer *) 0;
		return;
	}
	prom_timers = (struct sun5_timer *) ((unsigned long)addr[0]);
}