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
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 scalar_t__ from_oblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_oblock(dm_oblock_t lhs, dm_oblock_t rhs)
{
	if (from_oblock(lhs) < from_oblock(rhs))
		return -1;

	if (from_oblock(rhs) < from_oblock(lhs))
		return 1;

	return 0;
}