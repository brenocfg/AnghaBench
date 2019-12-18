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
struct TYPE_2__ {int n_src; int* src; } ;

/* Variables and functions */
 int NI_NAMES_BASE ; 

bool route_set_sources_in_order(const struct ni_device_routes *devroutes)
{
	int i;

	for (i = 0; i < devroutes->n_route_sets; ++i) {
		int j;
		int last = NI_NAMES_BASE - 1;

		for (j = 0; j < devroutes->routes[i].n_src; ++j) {
			if (last >= devroutes->routes[i].src[j])
				return false;
			last = devroutes->routes[i].src[j];
		}
	}
	return true;
}