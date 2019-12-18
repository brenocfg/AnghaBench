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
struct ni_route_set {int /*<<< orphan*/  n_src; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ni_bsearch_srccmp ; 
 int /*<<< orphan*/  bsearch (int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool ni_route_set_has_source(const struct ni_route_set *routes,
			     const int source)
{
	if (!bsearch(&source, routes->src, routes->n_src, sizeof(int),
		     _ni_bsearch_srccmp))
		return false;
	return true;
}