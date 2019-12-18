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
struct ni_route_set {int dummy; } ;
struct ni_device_routes {int /*<<< orphan*/  n_route_sets; int /*<<< orphan*/  routes; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ni_bsearch_destcmp ; 
 struct ni_route_set const* bsearch (int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

const struct ni_route_set *
ni_find_route_set(const int destination,
		  const struct ni_device_routes *valid_routes)
{
	return bsearch(&destination, valid_routes->routes,
		       valid_routes->n_route_sets, sizeof(struct ni_route_set),
		       _ni_bsearch_destcmp);
}