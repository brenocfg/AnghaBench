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
struct vl_arb_cache {int /*<<< orphan*/  table; } ;
struct ib_vl_weight_elem {int dummy; } ;

/* Variables and functions */
 int VL_ARB_TABLE_SIZE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,struct ib_vl_weight_elem*,int) ; 

__attribute__((used)) static int vl_arb_match_cache(struct vl_arb_cache *cache,
			      struct ib_vl_weight_elem *vl)
{
	return !memcmp(cache->table, vl, VL_ARB_TABLE_SIZE * sizeof(*vl));
}