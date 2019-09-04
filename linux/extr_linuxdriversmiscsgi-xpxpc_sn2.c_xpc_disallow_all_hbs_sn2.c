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
struct TYPE_2__ {int /*<<< orphan*/  heartbeating_to_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xp_max_npartitions ; 
 TYPE_1__* xpc_vars_sn2 ; 

__attribute__((used)) static void
xpc_disallow_all_hbs_sn2(void)
{
	DBUG_ON(xpc_vars_sn2 == NULL);
	bitmap_zero(xpc_vars_sn2->heartbeating_to_mask, xp_max_npartitions);
}