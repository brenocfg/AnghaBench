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
struct raid_type {int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int __within_range (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool rt_is_raid45(struct raid_type *rt)
{
	return __within_range(rt->level, 4, 5);
}