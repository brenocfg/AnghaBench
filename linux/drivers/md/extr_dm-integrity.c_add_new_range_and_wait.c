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
struct dm_integrity_range {int dummy; } ;
struct dm_integrity_c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_new_range (struct dm_integrity_c*,struct dm_integrity_range*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_and_add_new_range (struct dm_integrity_c*,struct dm_integrity_range*) ; 

__attribute__((used)) static void add_new_range_and_wait(struct dm_integrity_c *ic, struct dm_integrity_range *new_range)
{
	if (unlikely(!add_new_range(ic, new_range, true)))
		wait_and_add_new_range(ic, new_range);
}