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
struct TYPE_2__ {int /*<<< orphan*/  new_layout; } ;
struct raid_set {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  __is_raid10_far (int /*<<< orphan*/ ) ; 
 scalar_t__ rs_is_raid10 (struct raid_set*) ; 
 scalar_t__ rs_is_raid456 (struct raid_set*) ; 

__attribute__((used)) static bool rs_is_reshapable(struct raid_set *rs)
{
	return rs_is_raid456(rs) ||
	       (rs_is_raid10(rs) && !__is_raid10_far(rs->md.new_layout));
}