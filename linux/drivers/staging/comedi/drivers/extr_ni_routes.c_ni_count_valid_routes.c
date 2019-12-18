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
typedef  int /*<<< orphan*/  u8 ;
struct ni_route_tables {int /*<<< orphan*/ * route_values; TYPE_1__* valid_routes; } ;
struct ni_route_set {int n_src; int* src; int dest; } ;
struct TYPE_2__ {int n_route_sets; struct ni_route_set* routes; } ;

/* Variables and functions */
 int /*<<< orphan*/  B (int const) ; 
 int const NI_RGOUT0 ; 
 int const NI_RTSI_BRD (int) ; 
 scalar_t__ RVi (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ channel_is_rtsi (int const) ; 

unsigned int ni_count_valid_routes(const struct ni_route_tables *tables)
{
	int total = 0;
	int i;

	for (i = 0; i < tables->valid_routes->n_route_sets; ++i) {
		const struct ni_route_set *R = &tables->valid_routes->routes[i];
		int j;

		for (j = 0; j < R->n_src; ++j) {
			const int src  = R->src[j];
			const int dest = R->dest;
			const u8 *rv = tables->route_values;

			if (RVi(rv, B(src), B(dest)))
				/* direct routing is valid */
				++total;
			else if (channel_is_rtsi(dest) &&
				 (RVi(rv, B(src), B(NI_RGOUT0)) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(0))) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(1))) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(2))) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(3))))) {
				++total;
			}
		}
	}
	return total;
}