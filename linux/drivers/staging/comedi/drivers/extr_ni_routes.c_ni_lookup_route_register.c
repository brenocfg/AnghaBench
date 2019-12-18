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
struct ni_route_tables {int /*<<< orphan*/  route_values; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int B (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int NI_NUM_NAMES ; 
 int /*<<< orphan*/  RVi (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UNMARK (int /*<<< orphan*/ ) ; 

s8 ni_lookup_route_register(int src, int dest,
			    const struct ni_route_tables *tables)
{
	s8 regval;

	/*
	 * Be sure to use the B() macro to subtract off the NI_NAMES_BASE before
	 * indexing into the route_values array.
	 */
	src = B(src);
	dest = B(dest);
	if (src < 0 || src >= NI_NUM_NAMES || dest < 0 || dest >= NI_NUM_NAMES)
		return -EINVAL;
	regval = RVi(tables->route_values, src, dest);
	if (!regval)
		return -EINVAL;
	/* mask out the valid-value marking bit */
	return UNMARK(regval);
}