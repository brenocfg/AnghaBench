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
struct ni_device_routes {int n_route_sets; TYPE_1__* routes; } ;
struct TYPE_2__ {int dest; } ;

/* Variables and functions */
 int NI_NAMES_BASE ; 

__attribute__((used)) static bool route_set_dests_in_order(const struct ni_device_routes *devroutes)
{
	int i;
	int last = NI_NAMES_BASE - 1;

	for (i = 0; i < devroutes->n_route_sets; ++i) {
		if (last >= devroutes->routes[i].dest)
			return false;
		last = devroutes->routes[i].dest;
	}
	return true;
}