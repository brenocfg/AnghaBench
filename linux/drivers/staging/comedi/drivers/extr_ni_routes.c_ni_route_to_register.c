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
typedef  int /*<<< orphan*/  u8 ;
struct ni_route_tables {int /*<<< orphan*/ * route_values; int /*<<< orphan*/  valid_routes; } ;
struct ni_route_set {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  B (int const) ; 
 int BIT (int) ; 
 int const NI_RGOUT0 ; 
 int const NI_RTSI_BRD (int) ; 
 int RVi (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UNMARK (int) ; 
 scalar_t__ channel_is_rtsi (int const) ; 
 struct ni_route_set* ni_find_route_set (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_route_set_has_source (struct ni_route_set const*,int const) ; 

s8 ni_route_to_register(const int src, const int dest,
			const struct ni_route_tables *tables)
{
	const struct ni_route_set *routes =
		ni_find_route_set(dest, tables->valid_routes);
	const u8 *rv;
	s8 regval;

	/* first check to see if source is listed with bunch of destinations. */
	if (!routes)
		return -1;
	/* 2nd, check to see if destination is in list of source's targets. */
	if (!ni_route_set_has_source(routes, src))
		return -1;
	/*
	 * finally, check to see if we know how to route...
	 * Be sure to use the B() macro to subtract off the NI_NAMES_BASE before
	 * indexing into the route_values array.
	 */
	rv = tables->route_values;
	regval = RVi(rv, B(src), B(dest));

	/*
	 * if we did not validate the route, we'll see if we can route through
	 * one of the muxes
	 */
	if (!regval && channel_is_rtsi(dest)) {
		regval = RVi(rv, B(src), B(NI_RGOUT0));
		if (!regval && (RVi(rv, B(src), B(NI_RTSI_BRD(0))) ||
				RVi(rv, B(src), B(NI_RTSI_BRD(1))) ||
				RVi(rv, B(src), B(NI_RTSI_BRD(2))) ||
				RVi(rv, B(src), B(NI_RTSI_BRD(3)))))
			regval = BIT(6);
	}

	if (!regval)
		return -1;
	/* mask out the valid-value marking bit */
	return UNMARK(regval);
}