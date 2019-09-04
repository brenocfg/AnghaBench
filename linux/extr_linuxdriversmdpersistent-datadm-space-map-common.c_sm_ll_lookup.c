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
typedef  int uint32_t ;
struct ll_disk {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int sm_ll_lookup_big_ref_count (struct ll_disk*,int /*<<< orphan*/ ,int*) ; 
 int sm_ll_lookup_bitmap (struct ll_disk*,int /*<<< orphan*/ ,int*) ; 

int sm_ll_lookup(struct ll_disk *ll, dm_block_t b, uint32_t *result)
{
	int r = sm_ll_lookup_bitmap(ll, b, result);

	if (r)
		return r;

	if (*result != 3)
		return r;

	return sm_ll_lookup_big_ref_count(ll, b, result);
}