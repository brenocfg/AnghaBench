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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int MAX_NUMNODES ; 
 int distance_ref_points_depth ; 
 int /*<<< orphan*/  initialize_distance_lookup_table (int,int /*<<< orphan*/  const*) ; 
 int min_common_depth ; 
 int of_read_number (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int associativity_to_nid(const __be32 *associativity)
{
	int nid = -1;

	if (min_common_depth == -1)
		goto out;

	if (of_read_number(associativity, 1) >= min_common_depth)
		nid = of_read_number(&associativity[min_common_depth], 1);

	/* POWER4 LPAR uses 0xffff as invalid node */
	if (nid == 0xffff || nid >= MAX_NUMNODES)
		nid = -1;

	if (nid > 0 &&
		of_read_number(associativity, 1) >= distance_ref_points_depth) {
		/*
		 * Skip the length field and send start of associativity array
		 */
		initialize_distance_lookup_table(nid, associativity + 1);
	}

out:
	return nid;
}